/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICategoryManager">
 **/

package org.mozilla.xpcom;

public interface nsICategoryManager extends nsISupports
{
  public static final String NS_ICATEGORYMANAGER_IID =
    "{3275b2cd-af6d-429a-80d7-f0c5120342ac}";

  public String getCategoryEntry(String arg1, String arg2);

  public String addCategoryEntry(String arg1, String arg2, String arg3, boolean arg4, boolean arg5);

  public void deleteCategoryEntry(String arg1, String arg2, boolean arg3);

  public void deleteCategory(String arg1);

  public nsISimpleEnumerator enumerateCategory(String arg1);

  public nsISimpleEnumerator enumerateCategories();

}
