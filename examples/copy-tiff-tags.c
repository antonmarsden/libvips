/* Example showing how to call a couple of vips functions using an input
 * image file and creating an output file
 * also gathers some info on the input image
 */
#include <stdio.h>
#include <vips/vips.h>
#include <tiffio.h>

#define TIFFTAG_GEOPIXELSCALE       33550
#define TIFFTAG_GEOTIEPOINTS         33922
#define TIFFTAG_GEOTRANSMATRIX       34264
#define TIFFTAG_GEOKEYDIRECTORY      34735
#define TIFFTAG_GEODOUBLEPARAMS      34736
#define TIFFTAG_GEOASCIIPARAMS       34737

static const TIFFFieldInfo xtiffFieldInfo[] = {
	/* XXX Insert Your tags here */
	{ TIFFTAG_GEOPIXELSCALE,        -1,-1, TIFF_DOUBLE,     FIELD_CUSTOM,
		TRUE, TRUE,   "GeoPixelScale" },
	{ TIFFTAG_GEOTRANSMATRIX,       -1,-1, TIFF_DOUBLE,     FIELD_CUSTOM,
		TRUE, TRUE,   "GeoTransformationMatrix" },
	{ TIFFTAG_GEOTIEPOINTS, -1,-1, TIFF_DOUBLE,     FIELD_CUSTOM,
		TRUE, TRUE,   "GeoTiePoints" },
	{ TIFFTAG_GEOKEYDIRECTORY, -1,-1, TIFF_SHORT,   FIELD_CUSTOM,
		TRUE, TRUE,   "GeoKeyDirectory" },
	{ TIFFTAG_GEODOUBLEPARAMS,      -1,-1, TIFF_DOUBLE,     FIELD_CUSTOM,
		TRUE, TRUE,   "GeoDoubleParams" },
	{ TIFFTAG_GEOASCIIPARAMS,       -1,-1, TIFF_ASCII,      FIELD_CUSTOM,
		TRUE, FALSE,  "GeoASCIIParams" }
};

static const VipsForeignTiffTags customTiffTags = {
	tags: xtiffFieldInfo,
	len: sizeof(xtiffFieldInfo) / sizeof(xtiffFieldInfo[0])
};


int
main(int argc, char **argv)
{
	VipsImage *in;
	double mean;
	VipsImage *out;

	if (VIPS_INIT(argv[0]))
		vips_error_exit(NULL);

	if (argc != 3)
		vips_error_exit("usage: %s infile outfile", argv[0]);

	if (!(in = vips_image_new_from_file(argv[1], "customTags", &customTiffTags, NULL)))
		vips_error_exit(NULL);

	printf("image width = %d\n", vips_image_get_width(in));

	if (vips_avg(in, &mean, NULL))
		vips_error_exit(NULL);

	printf("mean pixel value = %g\n", mean);

	/* generate photo nexative - replace with other vips_ funcs */
	if (vips_invert(in, &out, NULL))
		vips_error_exit(NULL);

	g_object_unref(in);

	if (vips_image_write_to_file(out, argv[2], NULL))
		vips_error_exit(NULL);

	g_object_unref(out);

	return 0;
}
