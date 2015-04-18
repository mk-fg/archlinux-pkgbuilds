#include <archive.h>
#include <archive_entry.h>
#include <stdio.h>

const int BS = 16384;

int main(int argc, const char **argv) {
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [file]\n", argv[0]);
		return 1; }

	struct archive *a = archive_read_new();
	archive_read_support_compression_all(a);
	archive_read_support_format_raw(a);

	int err;
	if (argc == 2) err = archive_read_open_filename(a, argv[1], BS);
	else err = archive_read_open_fd(a, 0, BS);
	if (err != ARCHIVE_OK) {
		fprintf(stderr, "Broken archive (1)\n");
		return 1; }

	struct archive_entry *ae;
	err = archive_read_next_header(a, &ae);
	if (err != ARCHIVE_OK) {
		fprintf(stderr, "Broken archive (2)\n");
		return 1; }

	(void) archive_read_data_into_fd(a, 1);

	archive_read_finish(a);
	return 0;
}
