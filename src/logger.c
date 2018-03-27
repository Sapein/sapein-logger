#include "logger.h"
#include <stdlib.h>

/* Begin Forward Declaration of Private Functions related to the internals */
void _standard_free(struct logging *logger);
int _print_logger(struct logging *logger, enum Log_level level, char *msg);
int _print_err_logger(struct logging *logger, enum Log_level level, char *msg);
int _file_logger(struct logging *logger, enum Log_level level, char *msg);

void _user_defined_free(struct logging *logger);
int _user_logger_log(struct logging *logger, enum Log_level level, char *msg);
/* End Forward Declaration of Private Functions related to the internals */

logger create_logger(enum Log_type type, enum Log_level level, char *file){
  logger new_logger;
  new_logger.level = level;
  new_logger.type = type;
  if(type == PRINT){
    new_logger.file_handler.file_handle = NULL;
    new_logger.log = *_print_logger;
    new_logger.free_logger = *_standard_free;
  }else if(type == PRINT_ERR){
    new_logger.file_handler.file_handle = NULL;
    new_logger.log = *_print_err_logger;
    new_logger.free_logger = *_standard_free;
  }else if(type == FILE_LOG){
    new_logger.file_handler.file_handle = file;
    new_logger.log = *_file_logger;
    new_logger.free_logger = *_standard_free;
  }else if(type == USER){
    new_logger.file_handler.file_handle = NULL;
    new_logger.log = *_user_logger_log;
    new_logger.free_logger = *_user_defined_free;
  }
  return new_logger;
}
void register_log_func(logger *logger, int (*fn)(struct logging *, enum Log_level, char *msg)){
  logger->log = fn;
}
void register_free_func(logger *logger, void (*fn)(struct logging *)){
  logger->free_logger = fn;
}
void change_log_level(logger *logger, enum Log_level new_level){
  logger->level = new_level;
}

/* Private Functions designed to only be used in the implementation. Nothing should touch these ever */

/* Free Functions */
void _user_defined_free(struct logging *logger){
  fprintf(stderr, "No defined free function given!");
}

void _standard_free(struct logging *logger){
  free(logger);
}

/* Logging Functions */
/* All Logs should return the number of bytes written or mirror printf/fprintf */
int _print_logger(struct logging *logger, enum Log_level level, char *msg){
  if(logger->level <= level){
    return fprintf(stdin, "%s", msg);
  }else{
    return 0;
  }
}

int _print_err_logger(struct logging *logger, enum Log_level level, char *msg){
  if(logger->level <= level){
    return fprintf(stderr, "%s", msg);
  }else{
    return 0;
  }
}

int _file_logger(struct logging *logger, enum Log_level level, char *msg){
  FILE *file;
  int print_status;
  if(logger->level <= level){
    file = fopen(logger->file_handler.file_handle, "a");
    print_status = fprintf(file, "%s", msg);
    fclose(file);
    return print_status;
  }else{
    return 0;
  }
}

int _user_logger_log(struct logging *logger, enum Log_level level, char *msg){
  fprintf(stderr, "No defined log function given!");
  return 0;
}
