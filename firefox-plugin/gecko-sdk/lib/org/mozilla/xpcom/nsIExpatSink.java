/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIExpatSink">
 **/

package org.mozilla.xpcom;

public interface nsIExpatSink extends nsISupports
{
  public static final String NS_IEXPATSINK_IID =
    "{1deea160-c661-11d5-84cc-0010a4e0c706}";

  public void handleStartElement(String arg1, String[] arg2, long arg3, int arg4, long arg5);

  public void handleEndElement(String arg1);

  public void handleComment(String arg1);

  public void handleCDataSection(String arg1, long arg2);

  public void handleDoctypeDecl(String arg1, String arg2, String arg3, String arg4, nsISupports arg5);

  public void handleCharacterData(String arg1, long arg2);

  public void handleProcessingInstruction(String arg1, String arg2);

  public void handleXMLDeclaration(String arg1, String arg2, int arg3);

  public void reportError(String arg1, String arg2);

}
