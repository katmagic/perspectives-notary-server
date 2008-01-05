/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEditorMailSuppor">
 **/

package org.mozilla.xpcom;

public interface nsIEditorMailSupport extends nsISupports
{
  public static final String NS_IEDITORMAILSUPPORT_IID =
    "{fdf23301-4a94-11d3-9ce4-9960496c41bc}";

  public void pasteAsQuotation(int arg1);

  public nsIDOMNode insertAsQuotation(String arg1);

  public void insertTextWithQuotations(String arg1);

  public void pasteAsCitedQuotation(String arg1, int arg2);

  public nsIDOMNode insertAsCitedQuotation(String arg1, String arg2, boolean arg3);

  public void rewrap(boolean arg1);

  public void stripCites();

  public nsISupportsArray getEmbeddedObjects();

}
