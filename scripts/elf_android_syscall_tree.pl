#!/usr/bin/perl -w
use strict;
use warnings;
use POSIX qw(strtol);

my $objdump = shift;
my $syscall_file = shift;

open my $SC, "<", $syscall_file or die "Can't open syscall table!";
open my $CODE, "<", $objdump or die "Can't open ARM assembly file!";

my %syscalls;
my %extra_syscalls;
my $entrypoint = "";

require "scripts/syscall_filter.pl";
my %dowrap = always_wrap();
my %nowrap = never_wrap();
my %nowrap_re = never_wrap_re();

sub find_syscalls {
	my $sc_ref = shift;
	my %tmp_calls;

	seek $CODE, 0, 0;
	while (<$CODE>) {
		my $addr;
		my $val;
		my $ins;
		my $ops;

		# Set the entrypoint
		if (/^[0-9a-f]+ <([^>]+)>:.*/) {
			$entrypoint = $1;
			if (exists $dowrap{$entrypoint} and
			    !exists $extra_syscalls{$entrypoint} and
			    !exists $syscalls{$entrypoint}) {
			    	#warn "\talways_wrap:$entrypoint\n";
				$extra_syscalls{$entrypoint} = 1;
			}
			next;
		}
		if ($entrypoint eq "") { next; }

		# Parse a line of ARM dis-assembly to get the address,
		# raw hex instruction value, ASCII instruction, and operands
		if (/^\s+([0-9a-f]+):\t\s*([0-9a-f]+[ 0-9a-f]*)\s*\t([a-z.]+)\s*\t([^\s].*)$/) {
			($addr, my $unparsed) = strtol("0x$1");
			if ($unparsed != 0 || $!) {
				$addr = -1;
			}
			$val = $2;
			$ins = $3;
			$ops = $4;
			#warn "L|$1:\t$val\t$ins\t$ops\n"
		} else {
			next;
		}

		# Look for branches that target one of the syscalls
		if ($ins =~ /^b.*/ and $ops =~ /.*<(([_a-zA-Z]\w*)(\+0x[0-9a-fA-F]+)*)>.*/) {
			my $sc = $2;
			#warn "\t\t(b:$sc)\n";
			if ($sc eq $entrypoint) {
				# recursive function or in-function branch
				#warn "\t\t(r:$sc)\n";
				next;
			}
			if (exists $nowrap{$entrypoint}) { next; }
			my $dowrap = 1;
			foreach my $re (keys %nowrap_re) {
				if ($entrypoint =~ m/$re/) { $dowrap = 0; last; }
			}
			if ($dowrap == 0) { next; }
			if (exists $tmp_calls{$entrypoint} or
			    exists $extra_syscalls{$entrypoint} or
			    exists $syscalls{$entrypoint} or
			    exists $$sc_ref{$entrypoint}) {
				# we've already seen this one
				next;
			}
			if (exists $$sc_ref{$sc}) {
				# '$entrypoint' calls the system call '$sc'
				# warn "\t$entrypoint calls $sc\n";
				$tmp_calls{$entrypoint} = $sc;
				next;
			}
		}
	} # while (<$CODE>)

	if (scalar(keys %tmp_calls) == 0) {
		return;
	}

	# recurse and find entry points that call these entry points
	@extra_syscalls{keys %tmp_calls} = values %tmp_calls;
	find_syscalls(\%tmp_calls);
}

while (<$SC>) {
	/^\s*([_a-zA-Z]\w*)\s*$/;
	$syscalls{$1} = 1;
}

find_syscalls(\%syscalls);

# print out a space-separated list of new entry points to mark as syscalls
my $sc_list = join(" ", keys %extra_syscalls);
print "$sc_list";
