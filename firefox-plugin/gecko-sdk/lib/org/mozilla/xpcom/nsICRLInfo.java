/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICRLInfo">
 **/

package org.mozilla.xpcom;

public interface nsICRLInfo extends nsISupports
{
  public static final String NS_ICRLINFO_IID =
    "{c185d920-4a3e-11d5-ba27-00108303b117}";

  public String getOrganization();

  public String getOrganizationalUnit();

  public double getLastUpdate();

  public double getNextUpdate();

  public String getLastUpdateLocale();

  public String getNextUpdateLocale();

  public String getNameInDb();

  public String getLastFetchURL();

}
