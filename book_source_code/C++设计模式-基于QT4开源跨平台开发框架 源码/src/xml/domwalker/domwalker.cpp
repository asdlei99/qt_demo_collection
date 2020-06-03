#include <domwalker.h>

DomWalker::DomWalker(QDomDocument indoc) {
    m_Doc = indoc;
}



QDomElement DomWalker::createElement(QString name) {
    return m_Doc.createElement(name);
}

/**
   Recursive traversal - makes in place changes to a DOM tree.
   */
//start

QDomDocument DomWalker::transform() {
    walkTree(m_Doc);
    return m_Doc;
}

QDomNode DomWalker::walkTree(QDomNode current) {
    QDomNodeList dnl = current.childNodes();  /* First process
the children recursively. */
    for (int i=dnl.count()-1; i >=0; --i)
        walkTree(dnl.item(i));
    if (current.nodeType() == QDomNode::ElementNode) { /* We 
       only want to process elements, leaving all nodes unchanged. */
       QDomElement ce = current.toElement(); /* instead 
       of a typecast */
       return visit(ce);
    }
    return current;
}
//end

