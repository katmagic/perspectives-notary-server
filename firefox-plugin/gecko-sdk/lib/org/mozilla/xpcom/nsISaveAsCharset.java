/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISaveAsCharset">
 **/

package org.mozilla.xpcom;

public interface nsISaveAsCharset extends nsISupports
{
  public static final String NS_ISAVEASCHARSET_IID =
    "{33b87f70-7a9c-11d3-915c-006008a6edf6}";

  public static final long mask_Fallback = 255L;

  public static final long mask_Entity = 768L;

  public static final long mask_CharsetFallback = 1024L;

  public static final long mask_IgnorableFallback = 2048L;

  public static final long attr_FallbackNone = 0L;

  public static final long attr_FallbackQuestionMark = 1L;

  public static final long attr_FallbackEscapeU = 2L;

  public static final long attr_FallbackDecimalNCR = 3L;

  public static final long attr_FallbackHexNCR = 4L;

  public static final long attr_EntityNone = 0L;

  public static final long attr_EntityBeforeCharsetConv = 256L;

  public static final long attr_EntityAfterCharsetConv = 512L;

  public static final long attr_CharsetFallback = 1024L;

  public static final long attr_IgnoreIgnorables = 2048L;

  public static final long attr_plainTextDefault = 0L;

  public static final long attr_htmlTextDefault = 259L;

  public String getCharset();

  public void init(String arg1, long arg2, long arg3);

  public String convert(String arg1);

}
