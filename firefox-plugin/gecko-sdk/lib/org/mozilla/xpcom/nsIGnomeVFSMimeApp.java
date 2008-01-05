/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIGnomeVFSMimeApp">
 **/

package org.mozilla.xpcom;

public interface nsIGnomeVFSMimeApp extends nsISupports
{
  public static final String NS_IGNOMEVFSMIMEAPP_IID =
    "{99ae024f-e869-4973-958b-54768a84295a}";

  public static final int EXPECTS_URIS = 0;

  public static final int EXPECTS_PATHS = 1;

  public static final int EXPECTS_URIS_FOR_NON_FILES = 2;

  public String getId();

  public String getName();

  public String getCommand();

  public boolean getCanOpenMultipleFiles();

  public int getExpectsURIs();

  public nsIUTF8StringEnumerator getSupportedURISchemes();

  public boolean getRequiresTerminal();

}
