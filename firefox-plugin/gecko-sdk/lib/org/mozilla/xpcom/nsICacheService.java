/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICacheService">
 **/

package org.mozilla.xpcom;

public interface nsICacheService extends nsISupports
{
  public static final String NS_ICACHESERVICE_IID =
    "{de114eb4-29fc-4959-b2f7-2d03eb9bc771}";

  public nsICacheSession createSession(String arg1, int arg2, boolean arg3);

  public void visitEntries(nsICacheVisitor arg1);

  public void evictEntries(int arg1);

}
