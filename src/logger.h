/**
 * @file 
 * @brief The Reference file for my logger.
 * @author Sapeint
 * @version 1.0.0
 * @copyright MIT/Expat License.
 */ 
#ifndef SAPEINT_C_LOGGER
#define SAPEINT_C_LOGGER
#include <stdio.h>
/**
 * The level at which you wish to log.
 *
 * All higher levels debug the lower levels (so DEBUG causes the logging of ERROR, WARN, and INFO).  
 */
enum Log_level {DEBUG, /**< Used for Debug information, such as tracking things */
		ERROR, /**< This should be used for any unrecoverable errors */
		WARN,  /**< This should be used for errors or issues which are recoverable */
		INFO   /**< This should just use for standard output users might want to have */
               };

/** 
 * This is the type of Logger you wish to use
 *
 * The type of logger is how the logger stores the logs.
 *
 */
enum Log_type {NONE,      /**< No logging. This just doesn't initalize certain values */
	       PRINT,     /**< Logging with print to stdout (standard out). Basically a printf */   
	       PRINT_ERR, /**< Logging with print to stderr (standard error). */
	       FILE_LOG,  /**< Logging to a file. */
	       USER       /**< Logging that is user defined and implemented. */
              };

/**
 * This is a handler of files.
 *
 * Use this union mainly if you need to keep a file open until the freeing of a logger
 */
union log_file_handler {
  FILE *file_log;    /**< This is used to hold a file struct open. You should free it in free */
  char *file_handle; /**< This is used to hold a file name. FILE_LOG uses this by default */
};

/**
 * This is where the majority of things will occur.
 *
 * All logging functionality goes through here, you must make one of these before logging.
 */
struct logging {
  enum Log_type type; /**< The type of logger. This is mainly for managing things */
  enum Log_level level; /**< The level of logging for the logger. */
  union log_file_handler file_handler; /**< The handler of the file. See log_file_handler */
  /**
   * The function to actually log messages.
   * @warning This is only suggested to be called on the logger it is attached too.
   * @note this only prints out an error if you use the USER type. See register_log_func()
   * @param log The logger struct that exists. 
   * @param level The lowest level where you want the message to be logged.
   * @param msg The Character Message you want to log. 
   * @return The numbers of characters written. 
   *         Returns a 0 if the level is too low or negative for an error. 
   *         See your fprintf() documentation for error codes.
   */
  int (*log)(struct logging *log, enum Log_level level, char *msg);

  /**
   * The function to free a logger you no longer need.
   * 
   * @warning This method does _NOT_ need to be called during usage of the built-in modes. 
   *          By default this will just call free() on the struct.
   * @warning This is only suggested to be called on the logger it is attached too.
   * @note This will only print out an error if you use the USER type. See regsiter_free_func()
   * @param log The logger to be freed. 
   */
  void (*free_logger)(struct logging *log);
};
typedef struct logging logger; /**< This is just an alias for the logging struct */
/**
 * @def REMOVE_LOGGING
 * If this is defined all logging functions will be compiled out, although definitions will remain.
 *
 * This really shouldn't be used though.
 */
#ifndef REMOVE_LOGGING
/**
 * The function to create the logger.
 *
 * @warning if you use the USER type, you will need to define everything else.
 * @warning if you use the NONE type, nothing will be initialized.
 * 
 * @param type The type of the logger to create.
 * @param level The default level to set the logger at.
 * @param file The filename of the file you wish to log too. This may be set to NULL if you use PRINT.
 * @return Returns an initalized logger. 
 */
logger create_logger(enum Log_type type, enum Log_level level, char *file);
/**
 * Register a custom log function with the logger
 * @note you must use this is you use USER or NONE. otherwise it is suggested you avoid it.
 * 
 * @param log The logger to modify
 * @param fn The callback to set the log function too. 
 *        the parameter _MUST_ take a logger, a log_level, and a message. See struct logging.
 */
void register_log_func(logger *log, int (*fn)(struct logging *, enum Log_level, char *msg));

/**
 * Register a custom free function with the logger
 * @note you must use this is you use USER or NONE. otherwise it is suggested you avoid it.
 * 
 * @param log Which logger you want to free.
 * @param fn The callback to set the free function too. 
 *        the parameter _MUST_ take a pointer to a logger.
 */
void register_free_func(logger *log, void (*fn)(struct logging *));
/**
 * Change the logging level.
 * 
 * @param log The logger you wish to change the level of.
 * @param new_level The new level you wish to set the logger too.
 */
void change_log_level(logger *log, enum Log_level new_level);
#else
#define create_logger()       ;
#define register_log_func()   ;
#define register_free_func()  ;
#define change_log_level()    ;
#endif
#endif
