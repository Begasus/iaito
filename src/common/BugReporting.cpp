#include "BugReporting.h"

#include "Iaito.h"
#include "IaitoConfig.h"
#include <QDesktopServices>
#include <QJsonObject>
#include <QUrl>

void openIssue()
{
    QString url, osInfo, format, arch, type;
    // Pull in info needed for git issue
    osInfo = QSysInfo::productType() + " "
             + (QSysInfo::productVersion() == "unknown" ? "" : QSysInfo::productVersion());
    QJsonDocument docu = Core()->getFileInfo();
    QJsonObject coreObj = docu.object()["core"].toObject();
    QJsonObject binObj = docu.object()["bin"].toObject();
    if (!binObj.QJsonObject::isEmpty()) {
        format = coreObj["format"].toString();
        arch = binObj["arch"].toString();
        if (!binObj["type"].isUndefined()) {
            type = coreObj["type"].toString();
        } else {
            type = "N/A";
        }
    } else {
        format = coreObj["format"].toString();
        arch = "N/A";
        type = "N/A";
    }
    url = "https://github.com/radareorg/iaito/issues/new?&body=**Environment "
          "information**\n* Operating System: "
          + osInfo + "\n* Iaito version: " + IAITO_VERSION_FULL + "\n* File format: " + format
          + "\n * Arch: " + arch + "\n * Type: " + type
          + "\n\n**Describe the bug**\nA clear and concise description of what the "
            "bug is.\n\n**To Reproduce**\n"
            "Steps to reproduce the behavior:\n1. Go to '...'\n2. Click on "
            "'....'\n3. Scroll down to '....'\n"
            "4. See error\n\n**Expected behavior**\n"
            "A clear and concise description of what you expected to happen.\n\n"
            "**Screenshots**\nIf applicable, add screenshots to help explain your "
            "problem.\n\n"
            "**Additional context**\nAdd any other context about the problem here.";

    QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
}
