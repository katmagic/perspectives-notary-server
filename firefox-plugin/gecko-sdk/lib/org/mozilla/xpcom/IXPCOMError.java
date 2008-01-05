/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

package org.mozilla.xpcom;


/**
 * Mozilla XPCOM error codes.
 * <p>
 * THIS FILE GENERATED FROM mozilla/xpcom/base/nsError.h.
 * PLEASE SEE THAT FILE FOR FULL DOCUMENTATION.
 */
public interface IXPCOMError {

  public static final long NS_ERROR_MODULE_XPCOM = 1L;
  public static final long NS_ERROR_MODULE_BASE = 2L;
  public static final long NS_ERROR_MODULE_GFX = 3L;
  public static final long NS_ERROR_MODULE_WIDGET = 4L;
  public static final long NS_ERROR_MODULE_CALENDAR = 5L;
  public static final long NS_ERROR_MODULE_NETWORK = 6L;
  public static final long NS_ERROR_MODULE_PLUGINS = 7L;
  public static final long NS_ERROR_MODULE_LAYOUT = 8L;
  public static final long NS_ERROR_MODULE_HTMLPARSER = 9L;
  public static final long NS_ERROR_MODULE_RDF = 10L;
  public static final long NS_ERROR_MODULE_UCONV = 11L;
  public static final long NS_ERROR_MODULE_REG = 12L;
  public static final long NS_ERROR_MODULE_FILES = 13L;
  public static final long NS_ERROR_MODULE_DOM = 14L;
  public static final long NS_ERROR_MODULE_IMGLIB = 15L;
  public static final long NS_ERROR_MODULE_MAILNEWS = 16L;
  public static final long NS_ERROR_MODULE_EDITOR = 17L;
  public static final long NS_ERROR_MODULE_XPCONNECT = 18L;
  public static final long NS_ERROR_MODULE_PROFILE = 19L;
  public static final long NS_ERROR_MODULE_LDAP = 20L;
  public static final long NS_ERROR_MODULE_SECURITY = 21L;
  public static final long NS_ERROR_MODULE_DOM_XPATH = 22L;
  public static final long NS_ERROR_MODULE_DOM_RANGE = 23L;
  public static final long NS_ERROR_MODULE_URILOADER = 24L;
  public static final long NS_ERROR_MODULE_CONTENT = 25L;
  public static final long NS_ERROR_MODULE_PYXPCOM = 26L;
  public static final long NS_ERROR_MODULE_XSLT = 27L;
  public static final long NS_ERROR_MODULE_IPC = 28L;
  public static final long NS_ERROR_MODULE_SVG = 29L;
  public static final long NS_ERROR_MODULE_STORAGE = 30L;
  public static final long NS_ERROR_MODULE_SCHEMA = 31L;

  public static final long NS_ERROR_MODULE_GENERAL = 51L;

  public static final long NS_ERROR_SEVERITY_SUCCESS = 0L;
  public static final long NS_ERROR_SEVERITY_ERROR = 1L;

  public static final long NS_ERROR_MODULE_BASE_OFFSET = 0x45L;

  /* Standard "it worked" return value */
  public static final long NS_OK = 0L;

  public static final long NS_ERROR_BASE = 0xC1F30000L;

  /* Returned when an instance is not initialized */
  public static final long NS_ERROR_NOT_INITIALIZED = NS_ERROR_BASE + 1L;

  /* Returned when an instance is already initialized */
  public static final long NS_ERROR_ALREADY_INITIALIZED = NS_ERROR_BASE + 2L;

  /* Returned by a not implemented function */
  public static final long NS_ERROR_NOT_IMPLEMENTED = 0x80004001L;

  /* Returned when a given interface is not supported. */
  public static final long NS_NOINTERFACE = 0x80004002L;
  public static final long NS_ERROR_NO_INTERFACE = NS_NOINTERFACE;

  public static final long NS_ERROR_INVALID_POINTER = 0x80004003L;
  public static final long NS_ERROR_NULL_POINTER = NS_ERROR_INVALID_POINTER;

  /* Returned when a function aborts */
  public static final long NS_ERROR_ABORT = 0x80004004L;

  /* Returned when a function fails */
  public static final long NS_ERROR_FAILURE = 0x80004005L;

  /* Returned when an unexpected error occurs */
  public static final long NS_ERROR_UNEXPECTED = 0x8000ffffL;

  /* Returned when a memory allocation fails */
  public static final long NS_ERROR_OUT_OF_MEMORY = 0x8007000eL;

  /* Returned when an illegal value is passed */
  public static final long NS_ERROR_ILLEGAL_VALUE = 0x80070057L;
  public static final long NS_ERROR_INVALID_ARG = NS_ERROR_ILLEGAL_VALUE;

  /* Returned when a class doesn't allow aggregation */
  public static final long NS_ERROR_NO_AGGREGATION = 0x80040110L;

  /* Returned when an operation can't complete due to an unavailable resource */
  public static final long NS_ERROR_NOT_AVAILABLE = 0x80040111L;

  /* Returned when a class is not registered */
  public static final long NS_ERROR_FACTORY_NOT_REGISTERED = 0x80040154L;

  /* Returned when a class cannot be registered, but may be tried again later */
  public static final long NS_ERROR_FACTORY_REGISTER_AGAIN = 0x80040155L;

  /* Returned when a dynamically loaded factory couldn't be found */
  public static final long NS_ERROR_FACTORY_NOT_LOADED = 0x800401f8L;

  /* Returned when a factory doesn't support signatures */
  public static final long NS_ERROR_FACTORY_NO_SIGNATURE_SUPPORT = NS_ERROR_BASE + 0x101L;

  /* Returned when a factory already is registered */
  public static final long NS_ERROR_FACTORY_EXISTS = NS_ERROR_BASE + 0x100L;

  public static final long NS_ERROR_PROXY_INVALID_IN_PARAMETER = 0x80010010L;

  public static final long NS_ERROR_PROXY_INVALID_OUT_PARAMETER = 0x80010011L;

  /* I/O Errors */

  /*  Stream closed */
  public static final long NS_BASE_STREAM_CLOSED = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_BASE+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 2);
  /*  Error from the operating system */
  public static final long NS_BASE_STREAM_OSERROR = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_BASE+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 3);
  /*  Illegal arguments */
  public static final long NS_BASE_STREAM_ILLEGAL_ARGS = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_BASE+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 4);
  /*  For unichar streams */
  public static final long NS_BASE_STREAM_NO_CONVERTER = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_BASE+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 5);
  /*  For unichar streams */
  public static final long NS_BASE_STREAM_BAD_CONVERSION = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_BASE+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 6);

  public static final long NS_BASE_STREAM_WOULD_BLOCK = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_BASE+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 7);

  public static final long NS_ERROR_FILE_UNRECOGNIZED_PATH = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 1);
  public static final long NS_ERROR_FILE_UNRESOLVABLE_SYMLINK = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 2);
  public static final long NS_ERROR_FILE_EXECUTION_FAILED = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 3);
  public static final long NS_ERROR_FILE_UNKNOWN_TYPE = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 4);
  public static final long NS_ERROR_FILE_DESTINATION_NOT_DIR = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 5);
  public static final long NS_ERROR_FILE_TARGET_DOES_NOT_EXIST = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 6);
  public static final long NS_ERROR_FILE_COPY_OR_MOVE_FAILED = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 7);
  public static final long NS_ERROR_FILE_ALREADY_EXISTS = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 8);
  public static final long NS_ERROR_FILE_INVALID_PATH = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 9);
  public static final long NS_ERROR_FILE_DISK_FULL = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 10);
  public static final long NS_ERROR_FILE_CORRUPTED = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 11);
  public static final long NS_ERROR_FILE_NOT_DIRECTORY = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 12);
  public static final long NS_ERROR_FILE_IS_DIRECTORY = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 13);
  public static final long NS_ERROR_FILE_IS_LOCKED = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 14);
  public static final long NS_ERROR_FILE_TOO_BIG = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 15);
  public static final long NS_ERROR_FILE_NO_DEVICE_SPACE = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 16);
  public static final long NS_ERROR_FILE_NAME_TOO_LONG = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 17);
  public static final long NS_ERROR_FILE_NOT_FOUND = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 18);
  public static final long NS_ERROR_FILE_READ_ONLY = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 19);
  public static final long NS_ERROR_FILE_DIR_NOT_EMPTY = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 20);
  public static final long NS_ERROR_FILE_ACCESS_DENIED = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 21);

  public static final long NS_SUCCESS_FILE_DIRECTORY_EMPTY = ((NS_ERROR_SEVERITY_SUCCESS<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 1);

  /* Result codes used by nsIDirectoryServiceProvider2 */

  public static final long NS_SUCCESS_AGGREGATE_RESULT = ((NS_ERROR_SEVERITY_SUCCESS<<31) | ((NS_ERROR_MODULE_FILES+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 2);

  /* Result codes used by nsIVariant */

  public static final long NS_ERROR_CANNOT_CONVERT_DATA = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_XPCOM+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 1);
  public static final long NS_ERROR_OBJECT_IS_IMMUTABLE = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_XPCOM+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 2);
  public static final long NS_ERROR_LOSS_OF_SIGNIFICANT_DATA = ((NS_ERROR_SEVERITY_ERROR<<31) | ((NS_ERROR_MODULE_XPCOM+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 3);

  public static final long NS_SUCCESS_LOSS_OF_INSIGNIFICANT_DATA = ((NS_ERROR_SEVERITY_SUCCESS<<31) | ((NS_ERROR_MODULE_XPCOM+NS_ERROR_MODULE_BASE_OFFSET)<<16) | 1);

}
