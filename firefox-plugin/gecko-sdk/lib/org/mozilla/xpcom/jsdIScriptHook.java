/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+jsdIScriptHook">
 **/

package org.mozilla.xpcom;

public interface jsdIScriptHook extends nsISupports
{
  public static final String JSDISCRIPTHOOK_IID =
    "{ae89a7e2-1dd1-11b2-8c2f-af82086291a5}";

  public void onScriptCreated(jsdIScript arg1);

  public void onScriptDestroyed(jsdIScript arg1);

}
