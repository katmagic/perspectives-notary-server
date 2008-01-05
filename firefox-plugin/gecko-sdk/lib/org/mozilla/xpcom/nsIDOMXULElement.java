/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULElement">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULElement extends nsIDOMElement
{
  public static final String NS_IDOMXULELEMENT_IID =
    "{0574ed81-c088-11d2-96ed-00104b7b7deb}";

  public String getId();

  public void setId(String arg1);

  public String getClassName();

  public void setClassName(String arg1);

  public String getAlign();

  public void setAlign(String arg1);

  public String getDir();

  public void setDir(String arg1);

  public String getFlex();

  public void setFlex(String arg1);

  public String getFlexGroup();

  public void setFlexGroup(String arg1);

  public String getOrdinal();

  public void setOrdinal(String arg1);

  public String getOrient();

  public void setOrient(String arg1);

  public String getPack();

  public void setPack(String arg1);

  public boolean getHidden();

  public void setHidden(boolean arg1);

  public boolean getCollapsed();

  public void setCollapsed(boolean arg1);

  public String getObserves();

  public void setObserves(String arg1);

  public String getMenu();

  public void setMenu(String arg1);

  public String getContextMenu();

  public void setContextMenu(String arg1);

  public String getTooltip();

  public void setTooltip(String arg1);

  public String getWidth();

  public void setWidth(String arg1);

  public String getHeight();

  public void setHeight(String arg1);

  public String getMinWidth();

  public void setMinWidth(String arg1);

  public String getMinHeight();

  public void setMinHeight(String arg1);

  public String getMaxWidth();

  public void setMaxWidth(String arg1);

  public String getMaxHeight();

  public void setMaxHeight(String arg1);

  public String getPersist();

  public void setPersist(String arg1);

  public String getLeft();

  public void setLeft(String arg1);

  public String getTop();

  public void setTop(String arg1);

  public String getDatasources();

  public void setDatasources(String arg1);

  public String getRef();

  public void setRef(String arg1);

  public String getTooltipText();

  public void setTooltipText(String arg1);

  public String getStatusText();

  public void setStatusText(String arg1);

  public boolean getAllowEvents();

  public void setAllowEvents(boolean arg1);

  public nsIDOMCSSStyleDeclaration getStyle();

  public nsIRDFCompositeDataSource getDatabase();

  public nsIXULTemplateBuilder getBuilder();

  public nsIRDFResource getResource();

  public nsIControllers getControllers();

  public nsIBoxObject getBoxObject();

  public void focus();

  public void blur();

  public void click();

  public void doCommand();

  public nsIDOMNodeList getElementsByAttribute(String arg1, String arg2);

}
