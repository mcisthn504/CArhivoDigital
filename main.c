#include <stdio.h>
#include <stdlib.h>
#include "glib/poppler.h"

void extract_images(const char *input_pdf, const char *output_pdf) {
    // Initialize variables
    PopplerDocument *doc = NULL;
    GError *error = NULL;

    // Load the PDF document
    doc = poppler_document_new_from_file(input_pdf, NULL, &error);
    if (!doc) {
        fprintf(stderr, "Error loading PDF: %s\n", error->message);
        g_error_free(error);
        return;
    }

    // Get the number of pages in the document
    int num_pages = poppler_document_get_n_pages(doc);
    printf("Number of pages: %d\n", num_pages);

    // Iterate through pages
    for (int i = 0; i < num_pages; ++i) {
        PopplerPage *page = poppler_document_get_page(doc, i);
        if (!page) continue;

        // Extract images
        GList *image_list = poppler_page_get_image_mapping(page);
        int image_index = 0;

        for (GList *iter = image_list; iter; iter = iter->next, image_index++) {
            PopplerImageMapping *img_map = (PopplerImageMapping *)iter->data;

            // Only process images with indices that are multiples of 2
            if (image_index % 2 == 0) {
                cairo_surface_t *surface = poppler_page_get_image(page, img_map->image_id);

                // Save the image to output PDF (or separate files)
                char output_file[256];
                snprintf(output_file, sizeof(output_file), "output_image_%d.png", image_index);
                cairo_surface_write_to_png(surface, output_file);
                cairo_surface_destroy(surface);

                printf("Extracted image %d to %s\n", image_index, output_file);
            }
        }

        // Free resources
        g_list_free_full(image_list, g_free);
        g_object_unref(page);
    }

    // Free the document
    g_object_unref(doc);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_pdf> <output_pdf>\n", argv[0]);
        return 1;
    }

    const char *input_pdf = argv[1];
    const char *output_pdf = argv[2];

    extract_images(input_pdf, output_pdf);
    return 0;
}
