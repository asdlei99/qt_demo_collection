//start
#include <id3/tag.h>
#include <id3/misc_support.h>
#include <QString>

QString getStringField(ID3_Tag &tag, ID3_FrameID id,
    ID3_FieldID fieldid) {
        
    static char buffer[256];
    const int size=255;

    ID3_Frame* myFrame = tag.Find(id);
    if (myFrame) {
        ID3_Field *myField = myFrame->GetField(fieldid);
        if (myField)
            myField->Get(buffer, size);
    }
    return QString(buffer);
}


QString getPreference(QString filename) { /* gets the MusicMatch Preference */
    QString retval;

    ID3_Tag tag;
    tag.Link(filename.toAscii());

    QString commentType = getStringField(tag, ID3FID_COMMENT, 
                                         ID3FN_DESCRIPTION);
    if (commentType == "MusicMatch_Preference")  {
        retval = getStringField(tag, ID3FID_COMMENT, ID3FN_TEXT);
        return retval;
    } else
        return "Undefined";
}
//end

int main(int argc, char** argv) {
    return 0;
}
