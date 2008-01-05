/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXTFElement">
 **/

package org.mozilla.xpcom;

public interface nsIXTFElement extends nsISupports
{
  public static final String NS_IXTFELEMENT_IID =
    "{a8b607fd-24b6-4a8c-9a89-d9b24f8e2592}";

  public static final long ELEMENT_TYPE_GENERIC_ELEMENT = 0L;

  public static final long ELEMENT_TYPE_SVG_VISUAL = 1L;

  public static final long ELEMENT_TYPE_XML_VISUAL = 2L;

  public static final long ELEMENT_TYPE_XUL_VISUAL = 3L;

  public static final long ELEMENT_TYPE_BINDABLE = 4L;

  public static final long NOTIFY_WILL_CHANGE_DOCUMENT = 1L;

  public static final long NOTIFY_DOCUMENT_CHANGED = 2L;

  public static final long NOTIFY_WILL_CHANGE_PARENT = 4L;

  public static final long NOTIFY_PARENT_CHANGED = 8L;

  public static final long NOTIFY_WILL_INSERT_CHILD = 16L;

  public static final long NOTIFY_CHILD_INSERTED = 32L;

  public static final long NOTIFY_WILL_APPEND_CHILD = 64L;

  public static final long NOTIFY_CHILD_APPENDED = 128L;

  public static final long NOTIFY_WILL_REMOVE_CHILD = 256L;

  public static final long NOTIFY_CHILD_REMOVED = 512L;

  public static final long NOTIFY_WILL_SET_ATTRIBUTE = 1024L;

  public static final long NOTIFY_ATTRIBUTE_SET = 2048L;

  public static final long NOTIFY_WILL_REMOVE_ATTRIBUTE = 4096L;

  public static final long NOTIFY_ATTRIBUTE_REMOVED = 8192L;

  public static final long NOTIFY_BEGIN_ADDING_CHILDREN = 16384L;

  public static final long NOTIFY_DONE_ADDING_CHILDREN = 32768L;

  public static final long NOTIFY_HANDLE_DEFAULT = 65536L;

  public void onDestroyed();

  public long getElementType();

  public boolean getIsAttributeHandler();

  public String[] getScriptingInterfaces(long[] arg1);

  public void willChangeDocument(nsIDOMDocument arg1);

  public void documentChanged(nsIDOMDocument arg1);

  public void willChangeParent(nsIDOMElement arg1);

  public void parentChanged(nsIDOMElement arg1);

  public void willInsertChild(nsIDOMNode arg1, long arg2);

  public void childInserted(nsIDOMNode arg1, long arg2);

  public void willAppendChild(nsIDOMNode arg1);

  public void childAppended(nsIDOMNode arg1);

  public void willRemoveChild(long arg1);

  public void childRemoved(long arg1);

  public void willSetAttribute(nsIAtom arg1, String arg2);

  public void attributeSet(nsIAtom arg1, String arg2);

  public void willRemoveAttribute(nsIAtom arg1);

  public void attributeRemoved(nsIAtom arg1);

  public void beginAddingChildren();

  public void doneAddingChildren();

  public boolean handleDefault(nsIDOMEvent arg1);

  public void cloneState(nsIDOMElement arg1);

}
