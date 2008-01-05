/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMLSParserFilte">
 **/

package org.mozilla.xpcom;

public interface nsIDOMLSParserFilter extends nsISupports
{
  public static final String NS_IDOMLSPARSERFILTER_IID =
    "{10e8893d-ddf5-45d1-8872-615d72065fb4}";

  public static final short FILTER_ACCEPT = 1;

  public static final short FILTER_REJECT = 2;

  public static final short FILTER_SKIP = 3;

  public static final short FILTER_INTERRUPT = 4;

  public int startElement(nsIDOMElement arg1);

  public int acceptNode(nsIDOMNode arg1);

  public long getWhatToShow();

}
