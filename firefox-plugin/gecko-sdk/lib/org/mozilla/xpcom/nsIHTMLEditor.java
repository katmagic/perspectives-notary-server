/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHTMLEditor">
 **/

package org.mozilla.xpcom;

public interface nsIHTMLEditor extends nsISupports
{
  public static final String NS_IHTMLEDITOR_IID =
    "{afc36593-5787-4420-93d9-b2c0ccbf0cad}";

  public static final short eLeft = 0;

  public static final short eCenter = 1;

  public static final short eRight = 2;

  public static final short eJustify = 3;

  public void addDefaultProperty(nsIAtom arg1, String arg2, String arg3);

  public void removeDefaultProperty(nsIAtom arg1, String arg2, String arg3);

  public void removeAllDefaultProperties();

  public void setCSSInlineProperty(nsIAtom arg1, String arg2, String arg3);

  public void setInlineProperty(nsIAtom arg1, String arg2, String arg3);

  public void getInlineProperty(nsIAtom arg1, String arg2, String arg3, boolean[] arg4, boolean[] arg5, boolean[] arg6);

  public String getInlinePropertyWithAttrValue(nsIAtom arg1, String arg2, String arg3, boolean[] arg4, boolean[] arg5, boolean[] arg6);

  public void removeAllInlineProperties();

  public void removeInlineProperty(nsIAtom arg1, String arg2);

  public void increaseFontSize();

  public void decreaseFontSize();

  public boolean canDrag(nsIDOMEvent arg1);

  public void doDrag(nsIDOMEvent arg1);

  public void insertFromDrop(nsIDOMEvent arg1);

  public boolean nodeIsBlock(nsIDOMNode arg1);

  public void insertHTML(String arg1);

  public void pasteNoFormatting(int arg1);

  public void rebuildDocumentFromSource(String arg1);

  public void insertHTMLWithContext(String arg1, String arg2, String arg3, String arg4, nsIDOMDocument arg5, nsIDOMNode arg6, int arg7, boolean arg8);

  public void insertElementAtSelection(nsIDOMElement arg1, boolean arg2);

  public void setDocumentTitle(String arg1);

  public void updateBaseURL();

  public void selectElement(nsIDOMElement arg1);

  public void setCaretAfterElement(nsIDOMElement arg1);

  public void setParagraphFormat(String arg1);

  public String getParagraphState(boolean[] arg1);

  public String getFontFaceState(boolean[] arg1);

  public String getFontColorState(boolean[] arg1);

  public String getBackgroundColorState(boolean[] arg1);

  public String getHighlightColorState(boolean[] arg1);

  public void getListState(boolean[] arg1, boolean[] arg2, boolean[] arg3, boolean[] arg4);

  public void getListItemState(boolean[] arg1, boolean[] arg2, boolean[] arg3, boolean[] arg4);

  public void getAlignment(boolean[] arg1, short[] arg2);

  public void getIndentState(boolean[] arg1, boolean[] arg2);

  public void makeOrChangeList(String arg1, boolean arg2, String arg3);

  public void removeList(String arg1);

  public void indent(String arg1);

  public void align(String arg1);

  public nsIDOMElement getElementOrParentByTagName(String arg1, nsIDOMNode arg2);

  public nsIDOMElement getSelectedElement(String arg1);

  public String getHeadContentsAsHTML();

  public void replaceHeadContentsWithHTML(String arg1);

  public nsIDOMElement createElementWithDefaults(String arg1);

  public void insertLinkAroundSelection(nsIDOMElement arg1);

  public void setBackgroundColor(String arg1);

  public void setBodyAttribute(String arg1, String arg2);

  public void ignoreSpuriousDragEvent(boolean arg1);

  public nsISupportsArray getLinkedObjects();

  public boolean getIsCSSEnabled();

  public void setIsCSSEnabled(boolean arg1);

  public void addInsertionListener(nsIContentFilter arg1);

  public void removeInsertionListener(nsIContentFilter arg1);

  public nsIDOMElement createAnonymousElement(String arg1, nsIDOMNode arg2, String arg3, boolean arg4);

  public nsIDOMElement getSelectionContainer();

  public void checkSelectionStateForAnonymousButtons(nsISelection arg1);

  public boolean isAnonymousElement(nsIDOMElement arg1);

  public boolean getReturnInParagraphCreatesNewParagraph();

  public void setReturnInParagraphCreatesNewParagraph(boolean arg1);

}
