/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMLSParser">
 **/

package org.mozilla.xpcom;

public interface nsIDOMLSParser extends nsISupports
{
  public static final String NS_IDOMLSPARSER_IID =
    "{2a31a3a0-be68-40af-9f64-914192f0fba2}";

  public static final int ACTION_APPEND_AS_CHILDREN = 1;

  public static final int ACTION_REPLACE_CHILDREN = 2;

  public static final int ACTION_INSERT_BEFORE = 3;

  public static final int ACTION_INSERT_AFTER = 4;

  public static final int ACTION_REPLACE = 5;

  public nsIDOMDOMConfiguration getDomConfig();

  public nsIDOMLSParserFilter getFilter();

  public void setFilter(nsIDOMLSParserFilter arg1);

  public boolean getAsync();

  public boolean getBusy();

  public nsIDOMDocument parse(nsIDOMLSInput arg1);

  public nsIDOMDocument parseURI(String arg1);

  public nsIDOMNode parseWithContext(nsIDOMLSInput arg1, nsIDOMNode arg2, int arg3);

  public void abort();

}
