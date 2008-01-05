/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+rdfIDataSource">
 **/

package org.mozilla.xpcom;

public interface rdfIDataSource extends nsISupports
{
  public static final String RDFIDATASOURCE_IID =
    "{ebce86bd-1568-4a34-a808-9ccf9cde8087}";

  public void visitAllSubjects(rdfITripleVisitor arg1);

  public void visitAllTriples(rdfITripleVisitor arg1);

}
