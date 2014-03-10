#!/usr/bin/perl -w
use strict;
use POSIX qw(strtol);

my $entrypoint = "";
my $r7;
my $r7addr = 0;

require "scripts/api_filter.pl";
my %dowrap = always_wrap();
my %nowrap = never_wrap();
my %nowrap_re = never_wrap_re();

sub print_syscall {
	my $inum = shift;
	my $entry = shift;
	my $num;
	my $unparsed = 0;
	$! = 0;

	if (exists $nowrap{$entry}) { return; }
	foreach my $re (keys %nowrap_re) {
		if ($entry =~ m/$re/) { return; }
	}

	($num, $unparsed) = strtol($inum);
	if ($inum eq "" || $unparsed != 0 || $!) {
		$num = -1;
	}
	print "$num:$entry ";
	$entrypoint = "";
	$r7 = "";
	$r7addr = 0;
}

while (<>) {
	my $addr = $1;
	my $val = $2;
	my $ins = $3;
	my $ops = $4;

	if (/^[0-9a-f]+ <([^>]+)>:.*/) {
		$entrypoint = $1;
		$r7 = "";
		$r7addr = 0;
		next;
	}
	if ($entrypoint eq "") { next; }

	if (/^\s+([0-9a-f]+):\s+([0-9a-f]+)\s+([a-z]+)\s+([^\s].*)$/) {
		($addr, my $unparsed) = strtol("0x$1");
		if ($unparsed != 0 || $!) {
			$addr = -1;
		}
		$val = $2;
		$ins = $3;
		$ops = $4;
	} else {
		next;
	}

	if ($addr == $r7addr and $r7 eq "OK") {
		# the r7 value for a previous svc call
		print_syscall("0x$val", $entrypoint);
		next;
	}

	if ($ins =~ /^mov.*/ and $ops =~ /r7,\s*#(\d+)/) {
		$r7 = $1;
		next;
	}
	if ($ins =~ /^ldr.*/ and $ops =~ /r7,\s*\[pc,\s*#(\d+)\].*/) {
		$r7addr = $addr + $1 + 8;
		#print "\tINDIRECT: PC:$addr + $1 = $r7addr\n";
		next;
	}
	if ($ins eq "svc") {
		if ($r7addr) {
			$r7 = "OK";
			next;
		} else {
			print_syscall($r7, $entrypoint);
		}
	}
}
