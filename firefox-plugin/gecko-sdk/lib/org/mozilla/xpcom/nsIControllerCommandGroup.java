/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIControllerComman">
 **/

package org.mozilla.xpcom;

public interface nsIControllerCommandGroup extends nsISupports
{
  public static final String NS_ICONTROLLERCOMMANDGROUP_IID =
    "{9f82c404-1c7b-11d5-a73c-eca43ca836fc}";

  public void addCommandToGroup(String arg1, String arg2);

  public void removeCommandFromGroup(String arg1, String arg2);

  public boolean isCommandInGroup(String arg1, String arg2);

  public nsISimpleEnumerator getGroupsEnumerator();

  public nsISimpleEnumerator getEnumeratorForGroup(String arg1);

}
