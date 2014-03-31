#
# The wrapper "white list"
#

require "scripts/posix_api.pl";

my %_always_wrap = (
		    # Android specific routines
		    "bcopy" => 1,
		    "bzero" => 1,
		    "dlmalloc" => 1,
		    "dlcalloc" => 1,
		    "dlrealloc" => 1,
		    "dlrealloc_in_place" => 1,
		    "dlmemalign" => 1,
		    "dlposix_memalign" => 1,
		    "dlvalloc" => 1,
		    "dlpvalloc" => 1,
		    "dlfree" => 1,
		    "dlindependent_calloc" => 1,
		    "dlindependent_comalloc" => 1,
		    "dlbulk_free" => 1,
		    "dlmalloc_inspect_all" => 1,
		    "dlmalloc_trim" => 1,
		    "dlmalloc_footprint" => 1,
		    "dlmalloc_max_footprint" => 1,
		    "dlmalloc_footprint_limit" => 1,
		    "dlmalloc_set_footprint_limit" => 1,
		    "dlmallinfo" => 1,
		    "dlmallopt" => 1,
		    "dlmalloc_usable_size" => 1,
		    "valloc" => 1,
		    "pvalloc" => 1,
		    "memalign" => 1,
		    "__memcmp16" => 1,
		    "_fwalk" => 1,
		    "__sflush" => 1,
		    "__sflush_locked" => 1,
		    "__sclose" => 1,
		    "__sflags" => 1,
		    "statfs" => 1,
		    "fstatfs" => 1,
		    "fpurge" => 1,
		    "_cleanup" => 1,
		    "wait3" => 1,
		    "__wait4" => 1,
		    "basename" => 1,
		    "basename_r" => 1,
		    "dirname" => 1,
		    "dirname_r" => 1,
		    "issetugid" => 1,
		    "__sched_cpufree" => 1,
		    "freedtoa" => 1,
		    "__hostalias" => 1,
		    "__res_hostalias" => 1,
		    "getnetbyaddr" => 1,
		    "getnetbyname" => 1,
		    "getprotobyname" => 1,
		    "getprotobynumber" => 1,
		    "pthread_attr_getscope" => 1,
		    "setlocale" => 1,
		    "getgrouplist" => 1,
		    "getmntent" => 1,
		    "getusershell" => 1,
		    "setusershell" => 1,
		    "inet_nsap_addr" => 1,
		    "inet_nsap_ntoa" => 1,
		    "inet_aton" => 1,
		    "android_getnameinfoforiface" => 1,
		    "getservent_r" => 1,
		    "getopt_long" => 1,
		    "setlogmask_r" => 1,
		    "ether_aton_r" => 1,
		    "ether_aton" => 1,
		    "ether_ntoa_r" => 1,
		    "ether_ntoa" => 1,
		    "ftok" => 1,
		    "fts_open" => 1,
		    "fts_set" => 1,
		    "getpt" => 1,
		    "ldexp" => 1,
		    "MD5_Init" => 1,
		    "memmem" => 1,
		    "memrchr" => 1,
		    "memswap" => 1,
		    "timegm64" => 1,
		    "fake_localtime_r" => 1,
		    "fake_gmtime_r" => 1,
		    "mktime64" => 1,
		    "timelocal64" => 1,
		    "gmtime64_r" => 1,
		    "localtime64_r" => 1,
		    "asctime64_r" => 1,
		    "ctime64_r" => 1,
		    "localtime64" => 1,
		    "gmtime64" => 1,
		    "asctime64" => 1,
		    "ctime64" => 1,
		    "umount" => 1,
		    "setutent" => 1,
		    "getutent" => 1,
		    "endutent" => 1,
		    "hstrerror" => 1,
		    "__dn_skipname" => 1,
		    "__res_hnok" => 1,
		    "__res_ownok" => 1,
		    "__res_mailok" => 1,
		    "__res_dnok" => 1,
		    "__putshort" => 1,
		    "_getlong" => 1,
		    "_getshort" => 1,
		    "__res_send_setqhook" => 1,
		    "__res_send_setrhook" => 1,
		    "__sym_ston" => 1,
		    "__sym_ntos" => 1,
		    "__sym_ntop" => 1,
		    "__p_type" => 1,
		    "__p_section" => 1,
		    "__p_option" => 1,
		    "__p_rcode" => 1,
		    "__dn_count_labels" => 1,
		    "__p_secstodate" => 1,
		    "__res_nametoclass" => 1,
		    "__res_nametotype" => 1,
		    "__res_get_nibblesuffix" => 1,
		    "__res_get_nibblesuffix2" => 1,
		    "__res_getservers" => 1,
		    "res_setiface" => 1,
		    "__res_nopt" => 1,
		    "_resolv_set_default_iface" => 1,
		    "_resolv_set_iface_for_pid" => 1,
		    "_resolv_clear_iface_for_pid" => 1,
		    "__b64_ntop" => 1,
		    "__b64_pton" => 1,
		    "__ns_name_ntop" => 1,
		    "__ns_name_pton" => 1,
		    "__ns_name_ntol" => 1,
		    "__ns_name_unpack" => 1,
		    "__ns_name_pack" => 1,
		    "__ns_name_rollback" => 1,
		    "__ns_name_skip" => 1,
		    "__ns_skiprr" => 1,
		    "__ns_initparse" => 1,
		    "__ns_get16" => 1,
		    "__ns_get32" => 1,
		    "__ns_put16" => 1,
		    "__ns_makecanon" => 1,
);


sub always_wrap() {
	my %h;
	# POSIX API
	%h = posix_alg();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_arg();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_fs();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_ipc();
	@_always_wrap{ keys %h } = values %h;
	# skip posix_math
	%h = posix_mem();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_misc();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_net();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_proc();
	@_always_wrap{ keys %h } = values %h;
	# skip posix_string
	%h = posix_term();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_thread();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_time();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_users();
	@_always_wrap{ keys %h } = values %h;
	return %_always_wrap;
}

#
# The wrapper "black list"
# must be kept in-sync with wraplib.sh should_wrap_android_elf bash function
#

# regular expressions (keep this list short)
my %_never_wrap_re = ( '.*@plt.*' => 1,
		      '.*divmod.*' => 1,
		      '.*_(rd|rw|un|try)*lock[^a-zA-Z]*' => 1,
);
sub never_wrap_re() {
	return %_never_wrap_re;
}

# explicit symbols
my %_never_wrap = (
		   ".plt" => 1,
		   "__libc_init" => 1,
		   "__errno" => 1,
		   "__aeabi_atexit" => 1,
		   "__cxa_atexit" => 1,
		   "__cxa_finalize" => 1,
		   "__init_tls" => 1,
		   "__thread_entry" => 1,
		   "__set_tls" => 1,

		   # unwind functions
		   "_Unwind_Resume" => 1,
		   "___Unwind_Resume" => 1,
		   "_Unwind_Resume_or_Rethrow" => 1,
		   "___Unwind_Resume_or_Rethrow" => 1,
		   "_Unwind_Backtrace" => 1,
		   "___Unwind_Backtrace" => 1,
		   "_Unwind_GetDataRelBase" => 1,
		   "_Unwind_RaiseException" => 1,
		   "___Unwind_RaiseException" => 1,
		   "_Unwind_ForceUnwind" => 1,
		   "___Unwind_ForceUnwind" => 1,
		   "_Unwind_VRS_Set" => 1,
		   "_Unwind_VRS_Get" => 1,
		   "__gnu_Unwind_RaiseException" => 1,
		   "__gnu_Unwind_Backtrace" => 1,
		   "__gnu_unwind_execute" => 1,
		   "__gnu_unwind_frame" => 1,
		   "__gnu_Unwind_Find_exidx" => 1,
		   "__gnu_Unwind_Resume" => 1,
		   "__gnu_Unwind_Resume_or_Rethrow" => 1,
		   "__gnu_Unwind_ForceUnwind" => 1,
		   "__aeabi_unwind_cpp_pr0" => 1,
		   "__aeabi_unwind_cpp_pr1" => 1,

		   # string operations
		   "__strncat_chk" => 1,
		   "__strcpy_chk" => 1,
		   "__strncpy_chk" => 1,
		   "__strlen_chk" => 1,
		   "__strnlen_chk" => 1,
		   "__strcat_chk" => 1,
		   "__sprintf_chk" => 1,
		   "__strchr_chk" => 1,
		   "__strrchr_chk" => 1,

		   # math
		   "__aeabi_idiv" => 1,
		   "__aeabi_uidiv" => 1,

		   # pthread functions that can be expensive
		   # (to be removed)
		   #"pthread_self" => 1,
		   #"pthread_getspecific" => 1,
		   #"pthread_setspecific" => 1,

		   # memory allocation functions
		   # (to be removed)
		   #"memset" => 1,
		   #"memcpy" => 1,
		   #"free" => 1,
		   #"malloc" => 1,
		   #"calloc" => 1,
		   #"memcmp" => 1,
		   #"memmove" => 1,
		   #"realloc" => 1,
		   #"__memcpy_chk" => 1,
		   #"__memmove_chk" => 1,

		   # clock
		   #"clock_gettime" => 1,
);

sub never_wrap() {
	my %h;
	%h = posix_string();
	@_never_wrap{ keys %h } = values %h;
	%h = posix_math();
	@_never_wrap{ keys %h } = values %h;
	return %_never_wrap;
}

