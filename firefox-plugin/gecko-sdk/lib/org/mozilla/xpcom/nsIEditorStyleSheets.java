/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEditorStyleSheet">
 **/

package org.mozilla.xpcom;

public interface nsIEditorStyleSheets extends nsISupports
{
  public static final String NS_IEDITORSTYLESHEETS_IID =
    "{4805e682-49b9-11d3-9ce4-ed60bd6cb5bc}";

  public void replaceStyleSheet(String arg1);

  public void addStyleSheet(String arg1);

  public void replaceOverrideStyleSheet(String arg1);

  public void addOverrideStyleSheet(String arg1);

  public void removeStyleSheet(String arg1);

  public void removeOverrideStyleSheet(String arg1);

  public void enableStyleSheet(String arg1, boolean arg2);

}
