#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *args) {
  printf("started thread\n");
  void *handle = dlopen("target/debug/libtmp.so", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }

  dlerror();

  void (*test)();
  *(void **) (&test) = dlsym(handle, "test");

  char *error;
  if ((error = dlerror()) != NULL)  {
    fprintf(stderr, "%s\n", error);
    exit(1);
  }

  (*test)();
  dlclose(handle);
}

int main(int argc, char *argv[]) {
  pthread_t tid;

  int err = pthread_create(&tid, NULL, &thread, NULL);
  if (err) {
    fprintf(stderr, "Thread creation errored\n");
    exit(1);
  }

  err = pthread_join(tid, NULL);
  if (err) {
    fprintf(stderr, "Thread join failed\n");
    exit(1);
  }
}

