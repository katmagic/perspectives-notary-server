/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+jsdIStackFrame">
 **/

package org.mozilla.xpcom;

public interface jsdIStackFrame extends jsdIEphemeral
{
  public static final String JSDISTACKFRAME_IID =
    "{b6d50784-1dd1-11b2-a932-882246c6fe45}";

  public boolean getIsNative();

  public boolean getIsDebugger();

  public boolean getIsConstructing();

  public jsdIStackFrame getCallingFrame();

  public jsdIContext getExecutionContext();

  public String getFunctionName();

  public jsdIScript getScript();

  public long getPc();

  public long getLine();

  public jsdIValue getCallee();

  public jsdIValue getScope();

  public jsdIValue getThisValue();

  public boolean eval(String arg1, String arg2, long arg3, jsdIValue[] arg4);

}
