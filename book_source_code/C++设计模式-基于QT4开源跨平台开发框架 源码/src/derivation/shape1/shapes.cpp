#include "shapes.h"

    double Circle::area() {
        return(3.14159 * m_Radius * m_Radius);
    }

    double Rectangle::area() {
        return (m_Height * m_Width);
    }

    double Square::area() {
        return (Rectangle::area()); /* Calling base class
           version on 'this' */
    }
//end

    QString Circle::getName() {
        return (" CIRCLE ");
    }
    QString Circle::getDimensions(){
        return QString(" Radius = %1 ").arg(m_Radius);
    }

    QString Rectangle::getName() {
        return (" RECTANGLE ");
    }
    QString Rectangle::getDimensions() {
        return QString(" Height = %1 Width = %2 ").
               arg(m_Height).arg(m_Width);
    }
    QString Square::getName() {
        return (" SQUARE ");
    }
    QString Square::getDimensions() {
        return QString(" Height = %1  ").arg(m_Height);
    }


