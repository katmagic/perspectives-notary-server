/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULBuilderListen">
 **/

package org.mozilla.xpcom;

public interface nsIXULBuilderListener extends nsISupports
{
  public static final String NS_IXULBUILDERLISTENER_IID =
    "{ac46be8f-c863-4c23-84a2-d0fcc8dfa9f4}";

  public void willRebuild(nsIXULTemplateBuilder arg1);

  public void didRebuild(nsIXULTemplateBuilder arg1);

}
