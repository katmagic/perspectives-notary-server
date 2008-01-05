/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaCollection">
 **/

package org.mozilla.xpcom;

public interface nsISchemaCollection extends nsISupports
{
  public static final String NS_ISCHEMACOLLECTION_IID =
    "{427c5511-941b-48c0-9abc-8ec9ea5d964b}";

  public nsISchema getSchema(String arg1);

  public nsISchemaElement getElement(String arg1, String arg2);

  public nsISchemaAttribute getAttribute(String arg1, String arg2);

  public nsISchemaType getType(String arg1, String arg2);

}
