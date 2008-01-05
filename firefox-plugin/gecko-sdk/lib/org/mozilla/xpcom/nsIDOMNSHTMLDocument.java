/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNSHTMLDocumen">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNSHTMLDocument extends nsISupports
{
  public static final String NS_IDOMNSHTMLDOCUMENT_IID =
    "{79beb289-3644-4b54-9432-9fb993945629}";

  public int getWidth();

  public int getHeight();

  public String getAlinkColor();

  public void setAlinkColor(String arg1);

  public String getLinkColor();

  public void setLinkColor(String arg1);

  public String getVlinkColor();

  public void setVlinkColor(String arg1);

  public String getBgColor();

  public void setBgColor(String arg1);

  public String getFgColor();

  public void setFgColor(String arg1);

  public String getDomain();

  public void setDomain(String arg1);

  public nsIDOMHTMLCollection getEmbeds();

  public String getSelection();

  public nsIDOMDocument open(String arg1, boolean arg2);

  public void write();

  public void writeln();

  public void clear();

  public void captureEvents(int arg1);

  public void releaseEvents(int arg1);

  public void routeEvent(nsIDOMEvent arg1);

  public String getCompatMode();

  public nsIDOMHTMLCollection getPlugins();

  public String getDesignMode();

  public void setDesignMode(String arg1);

  public boolean execCommand(String arg1, boolean arg2, String arg3);

  public boolean execCommandShowHelp(String arg1);

  public boolean queryCommandEnabled(String arg1);

  public boolean queryCommandIndeterm(String arg1);

  public boolean queryCommandState(String arg1);

  public boolean queryCommandSupported(String arg1);

  public String queryCommandText(String arg1);

  public String queryCommandValue(String arg1);

}
