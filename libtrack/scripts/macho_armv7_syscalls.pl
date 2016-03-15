#!/usr/bin/perl -w
use strict;
use POSIX qw(strtol);

my $entrypoint = "";
my %syscalls;

require "scripts/api_filter.pl";
my %dowrap = always_wrap();
my %nowrap = never_wrap();
my %nowrap_re = never_wrap_re();

my $prio = "never";

if ($#ARGV + 1 >= 2) {
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
}

sub add_syscall {
	my $entrypoint = shift;
    # remove preceding _
    my $clean_name = substr($entrypoint, 1);

	if ($prio eq "never") {
		if (exists $nowrap{$clean_name}) { print "wont wrap $entrypoint\n";return; }
		foreach my $re (keys %nowrap_re) {
			if ($clean_name =~ m/$re/) { print "wont wrap $entrypoint\n";return; }
		}
	} elsif ($prio eq "always")  {
		if (not exists $dowrap{$clean_name}) {
			# check the never wrap list b/c it's
			# not in the always wrap list
			if (exists $nowrap{$clean_name}) { return; }
			foreach my $re (keys %nowrap_re) {
				if ($clean_name =~ m/$re/) { return; }
			}
		}
	}
    if (!exists $syscalls{$entrypoint}) { 
        $syscalls{$entrypoint} = 1;
    }
	#print "$entry ";
}

while (<>) {
	my $addr = $1;
	my $val = $2;
	my $ins = $3;
	my $ops = $4;

	if (/(^_{1,3}.+):$/) {
		$entrypoint = $1;
        #print "$entrypoint:\n";
		next;
	}
	if ($entrypoint eq "") { next; }

	if (/^([0-9a-f]+)\s+([0-9a-f]+)\s+([a-z]+)\s+([^\s].*).*$/) {
		$val = $2;
		$ins = $3;
		$ops = $4;
    } else {
        next;
    }
    if ($ins eq "svc") {
#        print "$entrypoint:\n";
		add_syscall($entrypoint);
	}
}

print join(" ", keys %syscalls);
