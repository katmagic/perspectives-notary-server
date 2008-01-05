/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSerializer">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSerializer extends nsISupports
{
  public static final String NS_IDOMSERIALIZER_IID =
    "{9fd4ba15-e67c-4c98-b52c-7715f62c9196}";

  public String serializeToString(nsIDOMNode arg1);

  public void serializeToStream(nsIDOMNode arg1, nsIOutputStream arg2, String arg3);

}
