/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULTemplateBuild">
 **/

package org.mozilla.xpcom;

public interface nsIXULTemplateBuilder extends nsISupports
{
  public static final String NS_IXULTEMPLATEBUILDER_IID =
    "{9da147a7-5854-49e3-a397-22ecdd93e96d}";

  public nsIDOMElement getRoot();

  public nsIRDFCompositeDataSource getDatabase();

  public void rebuild();

  public void refresh();

  public void addListener(nsIXULBuilderListener arg1);

  public void removeListener(nsIXULBuilderListener arg1);

}
