.TH CTAR 1 "September 2025" "ctar 1.0" "User Commands"
.SH NAME
ctar \- create, list, and extract tar archives

.SH SYNOPSIS
.B ctar
[\fIOPTIONS\fR]

.SH DESCRIPTION
.B ctar
is a simplified implementation of the POSIX tar utility.
It allows users to create, list, and extract tar archives
following the POSIX USTAR format.

Only one operating mode can be specified at a time.

.SH OPTIONS
.TP
.BR \-l ", " \-\-list " " \fIARCHIVE\fR
List the contents of the tar archive \fIARCHIVE\fR.

.TP
.BR \-e ", " \-\-extract " " \fIARCHIVE\fR
Extract all files and directories from the tar archive \fIARCHIVE\fR
into the current working directory.

.TP
.BR \-c ", " \-\-create " " \fIARCHIVE\fR " " \fIFILE...\fR
Create a tar archive named \fIARCHIVE\fR containing the specified files.

.TP
.BR \-v ", " \-\-verbose
Enable verbose mode. Displays detailed information about the
operations being performed.

.TP
.BR \-z ", " \-\-compress
Reserved for compression support (not implemented).

.TP
.BR \-h ", " \-\-help
Display a short help message and exit.

.SH USAGE RULES
.IP \(bu 2
Exactly one mode must be selected: list, extract, or create.
.IP \(bu 2
Options that require arguments (\fB\-l\fR, \fB\-e\fR, \fB\-c\fR) cannot be grouped
with other short options.
.IP \(bu 2
Verbose mode does not affect archive contents.

.SH EXAMPLES
.TP
List the contents of an archive:
.EX
ctar -l archive.tar
.EE

.TP
List contents with verbose output:
.EX
ctar -v --list archive.tar
.EE

.TP
Extract an archive:
.EX
ctar -e archive.tar
.EE

.TP
Create an archive:
.EX
ctar -c archive.tar file1.txt file2.txt dir/
.EE

.SH EXIT STATUS
.TP
.B 0
Successful execution.
.TP
.B EINVAL
Invalid arguments or conflicting options.
.TP
.B ENOENT
File or archive not found.
.TP
.B EISDIR
A directory was used where a file was expected.
.TP
.B ENAMETOOLONG
A file name exceeds the maximum supported length.
.TP
.B Other
Standard POSIX error codes may be returned on failure.

.SH LIMITATIONS
.IP \(bu 2
Only the POSIX USTAR format is supported.

.IP \(bu 2
-lv format is not implemented. -v -l is the right format.

.SH AUTHOR
Written by Paolo Hoogland.

.SH SEE ALSO
.BR tar (1),
.BR getopt (3),
.BR open (2),
.BR read (2),
.BR write (2)
