#!/usr/bin/perl -w
use strict;
use warnings;
use POSIX qw(strtol);

my $prio = "never";
if ($ARGV[0] eq "-prio") {
	if ($ARGV[1] eq "1") {
		$prio = "always";
	} elsif ($ARGV[1] eq "2") {
		$prio = "never";
	} else {
		die "Invalid -prio option: '$ARGV[1]'";
	}
	shift @ARGV;
	shift @ARGV;
}

my $objdump = shift;
my $syscall_file = shift;

open my $SC, "<", $syscall_file or die "Can't open syscall table!";
open my $CODE, "<", $objdump or die "Can't open ARM assembly file:$objdump!";

if (not $prio eq "always" and not $prio eq "never") {
	die "Invalid prio: '$prio'"
}

my %syscalls;
my %extra_syscalls;
my $entrypoint = "";

require "scripts/api_filter.pl";
my %dowrap = always_wrap();
my %nowrap = never_wrap();
my %nowrap_re = never_wrap_re();

sub find_syscalls {
	my $sc_ref = shift;
	my %tmp_calls;
    my $clean_name;
	seek $CODE, 0, 0;
	while (<$CODE>) {
		my $addr;
		#my $val;
		my $ins;
		my $ops;

		# Set the entrypoint
        # If the entrypoint is to be wrapped and is neither
        # in extra_syscalls nor in syscalls, add it to extra_syscalls
		if (/(^_{1,3}.+):$/) {
			$entrypoint = $1;
            $clean_name = substr($entrypoint, 1);
    		if ($prio eq "always") {
				# check always-wrap list first, then never wrap
				if (exists $dowrap{$clean_name} and
				    !exists $extra_syscalls{$entrypoint} and
				    !exists $syscalls{$entrypoint}) {
					$extra_syscalls{$entrypoint} = 1;
				}
			} else {
				# check never-wrap list first, then always wrap
				my $shouldwrap = 1;
				if (exists $nowrap{$clean_name}) {
					$shouldwrap = 0;
				} else {
					foreach my $re (keys %nowrap_re) {
						if ($clean_name =~ m/$re/) { $shouldwrap = 0; last; }
					}
				}
                if ($shouldwrap == 1 and
				    exists $dowrap{$clean_name} and
				    !exists $extra_syscalls{$entrypoint} and
				    !exists $syscalls{$entrypoint}) {
					#warn "\talways_wrap(!never):$entrypoint\n";
                    print "add entry: $entrypoint to extra syscalls\n";
					$extra_syscalls{$entrypoint} = 1;
				}
			}
            # go to next line
			next;
		}
		if ($entrypoint eq "") { next; }

		# Parse a line of ARMv7 dis-assembly to get the address,
		# ASCII instruction, and operands
		#if (/^([0-9a-f]+)\t\s*([0-9a-f]+)\t\s*([.a-z]+)(.*)$/) {
		if (/^([0-9a-f]+)\s+([.a-z]+)\s+([^\s]+.*)$/) {
            $addr = $1;
			$ins = $2;
			$ops = $3;
			#print "L|$addr:\t$val\t$ins\t$ops\n";
		} else {
			next;
		}

		# Look for branches that target one of the syscalls
		if ($ins =~ /^b.*/ and ($ops =~ /.*for: (.*)$/ or $ops =~ /^(_{1,3}.+)\s*$/)) {
            # $sc is the branch's target
			my $sc = $1;
			#warn "\t\t(b:$sc)\n";
			if ($sc eq $entrypoint) {
				#print "recursive:$entrypoint\n";
				next;
			}
            # check that the entrypoint is to be wrapped
			my $shouldwrap = 1;
			if ($prio eq "never") {
                # if it is blacklisted continue
				if (exists $nowrap{$clean_name}) {
					#print "forbidden:$entrypoint\n";
					next;
				}
				foreach my $re (keys %nowrap_re) {
					if ($clean_name =~ m/$re/) {
						#print "forbidden:$entrypoint\n"; $shouldwrap = 0;
						last;
					}
				}
			} else {
				if (not exists $dowrap{$clean_name}) {
					# check the never wrap list b/c it's
					# not in the always wrap list
					if (exists $nowrap{$clean_name}) { next; }
					foreach my $re (keys %nowrap_re) {
						if ($clean_name =~ m/$re/) { $shouldwrap = 0; last; }
					}
				}
			}
			if ($shouldwrap == 0) { next; }

			# print "should wrap entrypoint: $entrypoint with branch\n";
## #####################################################################
## If you get here, the entrypoint is not in static POSIX symbols
## and is not blacklisted. If it is branching to a previously wrapped
## entrypoint, wrap the current one also.
## #####################################################################
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
		} # if ( <branch> )
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
