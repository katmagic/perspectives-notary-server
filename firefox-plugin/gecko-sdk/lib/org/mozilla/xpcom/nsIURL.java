/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIURL">
 **/

package org.mozilla.xpcom;

public interface nsIURL extends nsIURI
{
  public static final String NS_IURL_IID =
    "{d6116970-8034-11d3-9399-00104ba0fd40}";

  public String getFilePath();

  public void setFilePath(String arg1);

  public String getParam();

  public void setParam(String arg1);

  public String getQuery();

  public void setQuery(String arg1);

  public String getRef();

  public void setRef(String arg1);

  public String getDirectory();

  public void setDirectory(String arg1);

  public String getFileName();

  public void setFileName(String arg1);

  public String getFileBaseName();

  public void setFileBaseName(String arg1);

  public String getFileExtension();

  public void setFileExtension(String arg1);

  public String getCommonBaseSpec(nsIURI arg1);

  public String getRelativeSpec(nsIURI arg1);

}
