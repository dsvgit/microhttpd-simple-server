#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "router.h"

static int ahc_echo(void * cls,
        struct MHD_Connection * connection,
        const char * url,
        const char * method, const char * version,
        const char * upload_data,
        size_t * upload_data_size, void ** ptr) {
  static int dummy;
  const char * page;
  struct MHD_Response * response;
  int ret;

  printf("url %s \n", url);

  if (0 != strcmp(method, "GET")) return MHD_NO;
  if (&dummy != *ptr) {
    *ptr = &dummy;
    return MHD_YES;
  }
  if (0 != *upload_data_size) return MHD_NO;
  page = get_page(url);
  *ptr = NULL;
  response = MHD_create_response_from_buffer (strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);
  return ret;
}

int main(int argc, char ** argv) {
  struct MHD_Daemon * d;
  if (argc != 2) {
    printf("%s PORT\n", argv[0]);
    return 1;
  }
  d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
           atoi(argv[1]),
           NULL,
           NULL,
           &ahc_echo,
           NULL,
           MHD_OPTION_END);
  if (d == NULL) return 1;
  printf("listening port %s..\n", argv[1]);
  (void) getc (stdin);
  MHD_stop_daemon(d);
  return 0;
}