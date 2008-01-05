/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMMediaList">
 **/

package org.mozilla.xpcom;

public interface nsIDOMMediaList extends nsISupports
{
  public static final String NS_IDOMMEDIALIST_IID =
    "{9b0c2ed7-111c-4824-adf9-ef0da6dad371}";

  public String getMediaText();

  public void setMediaText(String arg1);

  public long getLength();

  public String item(long arg1);

  public void deleteMedium(String arg1);

  public void appendMedium(String arg1);

}
