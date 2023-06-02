/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2023 UniPro <ugene@unipro.ru>
 * http://ugene.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <GTGlobals.h>
#include <base_dialogs/GTFileDialog.h>
#include <primitives/GTComboBox.h>
#include <primitives/GTLabel.h>
#include <primitives/GTMenu.h>
#include <primitives/GTTreeWidget.h>

#include <QDir>

#include <U2View/AnnotatedDNAViewFactory.h>
#include <U2View/AnnotationsTreeView.h>
#include <U2View/MaEditorFactory.h>

#include "GTTestsProjectRemoteRequest.h"
#include "GTUtilsAnnotationsTreeView.h"
#include "GTUtilsDocument.h"
#include "GTUtilsMdi.h"
#include "GTUtilsProjectTreeView.h"
#include "GTUtilsSequenceView.h"
#include "GTUtilsTaskTreeView.h"
#include "GTUtilsNotifications.h"
#include "GTUtilsWorkflowDesigner.h"
#include "runnables/ugene/corelibs/U2Gui/DownloadRemoteFileDialogFiller.h"
#include "runnables/ugene/ugeneui/DocumentFormatSelectorDialogFiller.h"
#include "runnables/ugene/ugeneui/NCBISearchDialogFiller.h"
#include "runnables/ugene/plugins/dna_export/GetSequenceByIdFiller.h"

namespace U2 {

namespace GUITest_common_scenarios_project_remote_request {

GUI_TEST_CLASS_DEFINITION(test_0001) {
    GTUtilsTaskTreeView::openView(os);

    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "3EZB", 3));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."}, GTGlobals::UseKey);
    GTUtilsTaskTreeView::cancelTask(os, "Download remote documents");
    GTUtilsTaskTreeView::waitTaskFinished(os);
}

GUI_TEST_CLASS_DEFINITION(test_0002) {
    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "NC_001363", 0));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."});
    GTUtilsSequenceView::checkSequenceViewWindowIsActive(os);
    GTUtilsDocument::isDocumentLoaded(os, "NC_001363.gb");
    GTUtilsDocument::checkDocument(os, "NC_001363.gb", AnnotatedDNAViewFactory::ID);
}

GUI_TEST_CLASS_DEFINITION(test_0003) {
    //    1. Select {File -> Access remote database} menu item in the main menu.
    //    2. Fill the dialog:
    //        Resource ID: NC_017775
    //        Database: NCBI GenBank (DNA sequence)
    //        Save to folder: any valid path
    //        Force download the appropriate sequence: unchecked
    //    and accept it.
    //    Expected state: after the downloading task finish a new document appears in the project, it contains an annotation table only.

    QDir().mkpath(sandBoxDir + "remote_request/test_0003");
    QList<DownloadRemoteFileDialogFiller::Action> actions;

    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, {"NC_017775"});
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "NCBI GenBank (DNA sequence)");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir + "remote_request/test_0003");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetForceSequenceDownload, false);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."});
    GTUtilsTaskTreeView::waitTaskFinished(os);

    QSet<GObjectType> acceptableTypes;
    acceptableTypes.insert(GObjectTypes::ANNOTATION_TABLE);
    GTUtilsProjectTreeView::checkObjectTypes(os, acceptableTypes, GTUtilsProjectTreeView::findIndex(os, "NC_017775.gb"));
}

GUI_TEST_CLASS_DEFINITION(test_0004) {
    //    1. Select {File -> Access remote database} menu item in the main menu.
    //    2. Fill the dialog:
    //        Resource ID: NC_017775
    //        Database: NCBI GenBank (DNA sequence)
    //        Save to folder: any valid path
    //        Force download the appropriate sequence: checked
    //    and accept it.
    //    Expected state: after the downloading task finish a new document appears in the project, it contains both a sequence and an annotation table.

    QDir().mkpath(sandBoxDir + "remote_request/test_0004");
    QList<DownloadRemoteFileDialogFiller::Action> actions;

    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, {"NC_017775"});
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "NCBI GenBank (DNA sequence)");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir + "remote_request/test_0004");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetForceSequenceDownload, true);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."});
    GTUtilsTaskTreeView::waitTaskFinished(os);

    GTUtilsDocument::isDocumentLoaded(os, "NC_017775.gb");
    GTUtilsDocument::checkDocument(os, "NC_017775.gb", AnnotatedDNAViewFactory::ID);
}

GUI_TEST_CLASS_DEFINITION(test_0005) {
    //    1. Select {File -> Access remote database} menu item in the main menu.
    //    2. Fill the dialog:
    //        Resource ID: ENSG00000205571 ENSG00000146463: space between IDs
    //        Database: ENSEMBL
    //        Save to folder: any valid path and accept it.
    //    Expected state: after the downloading task finish a new documents appears in the project

    QDir().mkpath(sandBoxDir + "remote_request/test_0005");

    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "ENSG00000205571 ENSG00000146463", 2, true, true, false, sandBoxDir + "remote_request/test_0005"));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."});

    GTUtilsSequenceView::checkSequenceViewWindowIsActive(os);
    GTUtilsTaskTreeView::waitTaskFinished(os);

    GTUtilsDocument::isDocumentLoaded(os, "ENSG00000205571.fa");
    GTUtilsDocument::checkDocument(os, "ENSG00000205571.fa", AnnotatedDNAViewFactory::ID);

    GTUtilsDocument::isDocumentLoaded(os, "ENSG00000146463.fa");
    GTUtilsDocument::checkDocument(os, "ENSG00000146463.fa", AnnotatedDNAViewFactory::ID);
}

GUI_TEST_CLASS_DEFINITION(test_0006) {
    //    1. Select {File -> Access remote database} menu item in the main menu.
    //    2. Fill the dialog:
    //        Resource ID: Q9IGQ6;A0N8V2: semicolon between IDs
    //        Database: SWISS-PROT
    //        Save to folder: any valid path and accept it.
    //    Expected state: after the downloading task finish a new documents appears in the project

    QDir().mkpath(sandBoxDir + "remote_request/test_0006");
    GTUtilsDialog::waitForDialog(os, new DocumentFormatSelectorDialogFiller(os, "Swiss-Prot"));

    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "Q9IGQ6;A0N8V2", 4, true, true, false, sandBoxDir + "remote_request/test_0006"));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."});
    GTUtilsTaskTreeView::waitTaskFinished(os);

    GTUtilsDocument::isDocumentLoaded(os, "Q9IGQ6.txt");
    GTUtilsDocument::checkDocument(os, "Q9IGQ6.txt", AnnotatedDNAViewFactory::ID);
    GTUtilsDocument::isDocumentLoaded(os, "A0N8V2.txt");
    GTUtilsDocument::checkDocument(os, "A0N8V2.txt", AnnotatedDNAViewFactory::ID);
}

GUI_TEST_CLASS_DEFINITION(test_0007) {
    //    1. Select {File -> Access remote database} menu item in the main menu.
    //    2. Check all databases.
    //    Expected state: "Force download the appropriate sequence" checkbox is visible only for NCBI databases.
    QList<DownloadRemoteFileDialogFiller::Action> actions;

    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "NCBI GenBank (DNA sequence)");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, true);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "NCBI protein sequence database");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, true);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "ENSEMBL");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, false);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "PDB");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, false);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "SWISS-PROT");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, false);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "UniProtKB/Swiss-Prot");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, false);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "UniProtKB/TrEMBL");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, false);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickCancel, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."}, GTGlobals::UseKey);
}

GUI_TEST_CLASS_DEFINITION(test_0008) {
    //    1. Select {File -> Search NCBI Genbak} menu item in the main menu.
    //    2. Search "human" in the "nucleotide" database. Download the first result.
    //    Expected state: the "Fetch Data from Remote Database" appears. It is filled with:
    //        Database: "NCBI GenBank (DNA sequence)", it the only database in the combobox.
    //        Output format: "gb".
    //        "Force download the appropriate sequence" checkbox is visible and checked.
    //    3. Set "fasta" format.
    //    Expected state: "Force download the appropriate sequence" checkbox becomes invisible.
    QList<NcbiSearchDialogFiller::Action> searchActions;
    QList<DownloadRemoteFileDialogFiller::Action> downloadActions;

    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::SetTerm, qVariantFromValue(intStrStrPair(0, "human")));
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::SetDatabase, "nucleotide");
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::ClickSearch, "");
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::WaitTasksFinish, "");
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::ClickResultByNum, 0);

    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckDatabase, "NCBI GenBank (DNA sequence)");
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckDatabasesCount, 1);
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckOutputFormat, "gb");
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, true);
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownload, true);

    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetOutputFormat, "fasta");
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, false);
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickCancel, "");

    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::ClickDownload, qVariantFromValue(downloadActions));
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::ClickClose, "");

    GTUtilsDialog::waitForDialog(os, new NcbiSearchDialogFiller(os, searchActions));
    GTMenu::clickMainMenuItem(os, {"File", "Search NCBI GenBank..."});
}

GUI_TEST_CLASS_DEFINITION(test_0009) {
    //    1. Select {File -> Search NCBI Genbak} menu item in the main menu.
    //    2. Search "human" in the "protein" database. Download the first result.
    //    Expected state: the "Fetch Data from Remote Database" appears. It is filled with:
    //        Database: "NCBI protein sequence database", it the only database in the combobox.
    //        Output format: "gb".
    //        "Force download the appropriate sequence" checkbox is visible and checked.
    //    3. Set "fasta" format.
    //    Expected state: "Force download the appropriate sequence" checkbox becomes invisible.
    QList<NcbiSearchDialogFiller::Action> searchActions;
    QList<DownloadRemoteFileDialogFiller::Action> downloadActions;

    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::SetTerm, qVariantFromValue(intStrStrPair(0, "human")));
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::SetDatabase, "protein");
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::ClickSearch, "");
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::WaitTasksFinish, "");
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::ClickResultByNum, 0);

    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckDatabase, "NCBI protein sequence database");
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckDatabasesCount, 1);
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckOutputFormat, "gb");
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, true);
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownload, true);

    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetOutputFormat, "fasta");
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::CheckForceSequenceDownloadVisibility, false);
    downloadActions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickCancel, "");

    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::ClickDownload, qVariantFromValue(downloadActions));
    searchActions << NcbiSearchDialogFiller::Action(NcbiSearchDialogFiller::ClickClose, "");

    GTUtilsDialog::waitForDialog(os, new NcbiSearchDialogFiller(os, searchActions));
    GTMenu::clickMainMenuItem(os, {"File", "Search NCBI GenBank..."});
}

GUI_TEST_CLASS_DEFINITION(test_0010) {
    //    Test worker's GUI

    //    1. Open WD, set "Read Sequence rom Remote Database" element to the scene, select it.
    //    Expected state:
    //        Database: required, "NCBI GenBank (DNA sequence)";
    //        Read resource ID(s) from source: required, "List of IDs";
    //        Resource ID(s): required, visible;
    //        File with resource IDs: invisible;
    //        Save file to folder: required.

    //    2. Set parameter "Read resource ID(s) from source" to "File with IDs".
    //    Expected state:
    //        Resource ID(s): invisible;
    //        File with resource IDs: required, visible.
    GTUtilsWorkflowDesigner::openWorkflowDesigner(os);
    GTUtilsWorkflowDesigner::addAlgorithm(os, "Read Sequence from Remote Database");
    GTUtilsWorkflowDesigner::click(os, "Read Sequence from Remote Database");

    const QString database = GTUtilsWorkflowDesigner::getParameter(os, "Database");
    const QString source = GTUtilsWorkflowDesigner::getParameter(os, "Read resource ID(s) from source");
    CHECK_SET_ERR("NCBI GenBank (DNA sequence)" == database, QString("An unexpected default 'Database' value: expect '%1', got'%2'").arg("NCBI GenBank (DNA sequence)").arg(database));
    CHECK_SET_ERR("List of IDs" == source, QString("An unexpected default 'Read resource ID(s) from source' value: expect '%1', got'%2'").arg("List of IDs").arg(source));

    CHECK_SET_ERR(GTUtilsWorkflowDesigner::isParameterRequired(os, "Database"), "The 'Database' parameter is not required unexpectedly");
    CHECK_SET_ERR(GTUtilsWorkflowDesigner::isParameterRequired(os, "Read resource ID(s) from source"), "The 'Read resource ID(s) from source' parameter is not required unexpectedly");
    CHECK_SET_ERR(GTUtilsWorkflowDesigner::isParameterRequired(os, "Resource ID(s)"), "The 'Resource ID(s)' parameter is not required unexpectedly");
    CHECK_SET_ERR(GTUtilsWorkflowDesigner::isParameterRequired(os, "Save file to folder"), "The 'Save file to folder' parameter is not required unexpectedly");
    CHECK_SET_ERR(GTUtilsWorkflowDesigner::isParameterVisible(os, "Resource ID(s)"), "The 'Resource ID(s)' parameter is not visible unexpectedly");
    CHECK_SET_ERR(!GTUtilsWorkflowDesigner::isParameterVisible(os, "File with resource IDs"), "The 'File with resource IDs' parameter is visible unexpectedly");

    GTUtilsWorkflowDesigner::setParameter(os, "Read resource ID(s) from source", 0, GTUtilsWorkflowDesigner::comboValue);
    CHECK_SET_ERR(!GTUtilsWorkflowDesigner::isParameterVisible(os, "Resource ID(s)"), "The 'Resource ID(s)' parameter is visible unexpectedly");
    CHECK_SET_ERR(GTUtilsWorkflowDesigner::isParameterRequired(os, "File with resource IDs"), "The 'File with resource IDs' parameter is not required unexpectedly");
    CHECK_SET_ERR(GTUtilsWorkflowDesigner::isParameterVisible(os, "File with resource IDs"), "The 'File with resource IDs' parameter is not visible unexpectedly");
}

GUI_TEST_CLASS_DEFINITION(test_0011) {
    //    1.  File->Access remote database...
    //    2.  Fill    "Resource ID": 1ezg
    //                "Database": PDB
    //                "Add to project": true
    //        Open.
    //    3.  Expected state: 1ezg appears in a project view.

    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "1ezg", 3, true, true, false, sandBoxDir));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."}, GTGlobals::UseKey);

    GTUtilsSequenceView::checkSequenceViewWindowIsActive(os);
    GTUtilsDocument::isDocumentLoaded(os, "1ezg.pdb");
}

GUI_TEST_CLASS_DEFINITION(test_0012) {
    //    1.  File->Access remote database...
    //    2.  Fill    "Resource ID": 1ezg
    //                "Database": PDB
    //                "Add to project": false
    //        Open.
    //    3.  Expected state: 1ezg doesn't appear in a project view.

    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "1ezg", 3, false, true, false, sandBoxDir));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."}, GTGlobals::UseKey);

    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "1CRN", 3, true, true, false, sandBoxDir));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."}, GTGlobals::UseKey);

    GTUtilsDocument::isDocumentLoaded(os, "1CRN.pdb");

    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsProjectTreeView::checkNoItem(os, "1ezg.pdb");
}

GUI_TEST_CLASS_DEFINITION(test_0013) {
    //    1. Select {File -> Access remote database} menu item in the main menu.
    //    2. Fill the dialog:
    //        Resource ID: P16152
    //        Database: UniProtKB/Swiss-Prot
    //        Save to folder: any valid path and accept it.
    //    Expected state: after the downloading task finish a new documents appears in the project

    QDir().mkpath(sandBoxDir + "remote_request/test_0013");
    QList<DownloadRemoteFileDialogFiller::Action> actions;

    GTUtilsDialog::waitForDialog(os, new DocumentFormatSelectorDialogFiller(os, "Swiss-Prot"));
    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "P16152", 5, true, true, false, sandBoxDir));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."});
    GTUtilsTaskTreeView::waitTaskFinished(os);

    GTUtilsDocument::isDocumentLoaded(os, "P16152.txt");
    GTUtilsDocument::checkDocument(os, "P16152.txt", AnnotatedDNAViewFactory::ID);
}
GUI_TEST_CLASS_DEFINITION(test_0014) {
    //    1. Select {File -> Access remote database} menu item in the main menu.
    //    2. Fill the dialog:
    //        Resource ID: D0VTW9
    //        Database: UniProtKB/TrEMBL
    //        Save to folder: any valid path and accept it.
    //    Expected state: after the downloading task finish a new documents appears in the project

    QDir().mkpath(sandBoxDir + "remote_request/test_0014");
    GTUtilsDialog::waitForDialog(os, new DocumentFormatSelectorDialogFiller(os, "Swiss-Prot"));

    GTUtilsDialog::waitForDialog(os, new RemoteDBDialogFillerDeprecated(os, "D0VTW9", 6, true, true, false, sandBoxDir));
    GTMenu::clickMainMenuItem(os, {"File", "Access remote database..."});
    GTUtilsTaskTreeView::waitTaskFinished(os);

    GTUtilsDocument::isDocumentLoaded(os, "D0VTW9.txt");
    GTUtilsDocument::checkDocument(os, "D0VTW9.txt", AnnotatedDNAViewFactory::ID);
}

GUI_TEST_CLASS_DEFINITION(test_0015) {
    GTUtilsTaskTreeView::openView(os);

    class CheckLinks : public CustomScenario {
        void run(GUITestOpStatus& os) override {
            QWidget* dialog = GTWidget::getActiveModalWidget(os);

            static const QMap<QString, QString> DATABASE_LINK_MAP
                = { {"NCBI GenBank (DNA sequence)", "https://www.ncbi.nlm.nih.gov/nucleotide"},
                    {"NCBI protein sequence database", "https://www.ncbi.nlm.nih.gov/protein"},
                    {"ENSEMBL", "https://www.ensembl.org"},
                    {"PDB", "https://www.rcsb.org"},
                    {"SWISS-PROT", "https://www.uniprot.org"},
                    {"UniProtKB/Swiss-Prot", "https://www.uniprot.org"},
                    {"UniProtKB/TrEMBL", "https://www.uniprot.org"} };

            auto dbs = GTComboBox::getValues(os, GTWidget::findComboBox(os, "databasesBox", dialog));
            CHECK_SET_ERR(dbs.size() == DATABASE_LINK_MAP.size(), "Unexpected DBs size");

            for (const auto& db : qAsConst(dbs)) {
                const auto& link = DATABASE_LINK_MAP.value(db);
                CHECK_SET_ERR(!link.isEmpty(), QString("Unexpected db: %1").arg(db));

                GTComboBox::selectItemByText(os, "databasesBox", dialog, db);
                auto text = GTLabel::getText(os, "lbExternalLink", dialog);
                CHECK_SET_ERR(text.contains(link), QString("The %1 has no link, text: %2").arg(db).arg(text));
            }

            GTUtilsDialog::clickButtonBox(os, QDialogButtonBox::Cancel);
        }
    };

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, new CheckLinks));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);

}

GUI_TEST_CLASS_DEFINITION(test_0016_1) {
    QList<DownloadRemoteFileDialogFiller::Action> actions;
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "NCBI GenBank (DNA sequence)");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, "NC_001363");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.ncbi.nlm.nih.gov/nucleotide/NC_001363?report=genbank");
}

GUI_TEST_CLASS_DEFINITION(test_0016_2) {
    QList<DownloadRemoteFileDialogFiller::Action> actions;
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "NCBI protein sequence database");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, "AAA59172.1");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.ncbi.nlm.nih.gov/protein/AAA59172.1?report=genbank");
}

GUI_TEST_CLASS_DEFINITION(test_0016_3) {
    QList<DownloadRemoteFileDialogFiller::Action> actions;
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "ENSEMBL");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, "ENSG00000205571");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.ensembl.org/id/ENSG00000205571");
}

GUI_TEST_CLASS_DEFINITION(test_0016_4) {
    QList<DownloadRemoteFileDialogFiller::Action> actions;
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "PDB");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, "3INS");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.rcsb.org/structure/3INS");
}

GUI_TEST_CLASS_DEFINITION(test_0016_5) {
    QList<DownloadRemoteFileDialogFiller::Action> actions;
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "SWISS-PROT");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, "Q9IGQ6");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTUtilsDialog::add(os, new DocumentFormatSelectorDialogFiller(os, "Swiss-Prot"));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.uniprot.org/uniprotkb/Q9IGQ6/entry");
}

GUI_TEST_CLASS_DEFINITION(test_0016_6) {
    QList<DownloadRemoteFileDialogFiller::Action> actions;
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "UniProtKB/Swiss-Prot");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, "P16152");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTUtilsDialog::add(os, new DocumentFormatSelectorDialogFiller(os, "Swiss-Prot"));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.uniprot.org/uniprotkb/P16152/entry");
}

GUI_TEST_CLASS_DEFINITION(test_0016_7) {
    QList<DownloadRemoteFileDialogFiller::Action> actions;
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "UniProtKB/TrEMBL");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, "D0VTW9");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::EnterSaveToDirectoryPath, sandBoxDir);
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTUtilsDialog::add(os, new DocumentFormatSelectorDialogFiller(os, "Swiss-Prot"));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.uniprot.org/uniprotkb/D0VTW9/entry");
}

GUI_TEST_CLASS_DEFINITION(test_0017) {
    GTFileDialog::openFile(os, testDir + "_common_data/genbank/murine_cut.gb");
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsAnnotationsTreeView::expandItem(os, "CDS");
    GTTreeWidget::click(os, GTUtilsAnnotationsTreeView::findItem(os, "db_xref"), AnnotationsTreeView::COLUMN_VALUE);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.uniprot.org/uniprotkb/P03334/entry");
}

GUI_TEST_CLASS_DEFINITION(test_0018) {
    GTFileDialog::openFile(os, dataDir + "samples/Genbank/murine.gb");
    GTUtilsTaskTreeView::waitTaskFinished(os);

    GTUtilsSequenceView::clickAnnotationPan(os, "CDS", 1042);
    GTUtilsDialog::waitForDialog(os, new GetSequenceByIdFiller(os, sandBoxDir, true));
    GTUtilsDialog::waitForDialog(os, new PopupChooserByText(os, { "Fetch sequences from remote database",
                                                                  "Fetch sequences by 'db_xref' from 'CDS'" }));
    GTMenu::showContextMenu(os, GTUtilsSequenceView::getPanOrDetView(os));
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, "https://www.uniprot.org/uniprotkb/P03334/entry");
}

GUI_TEST_CLASS_DEFINITION(test_0019) {
    QList<DownloadRemoteFileDialogFiller::Action> actions;
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetDatabase, "NCBI GenBank (DNA sequence)");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::SetResourceIds, "qwerty,NC_001363");
    actions << DownloadRemoteFileDialogFiller::Action(DownloadRemoteFileDialogFiller::ClickOk, "");

    //GTUtilsNotifications::waitForNotification(os, false, "Failed to download");
    GTUtilsDialog::waitForDialog(os, new DownloadRemoteFileDialogFiller(os, actions));
    GTMenu::clickMainMenuItem(os, { "File", "Access remote database..." }, GTGlobals::UseKey);
    GTUtilsTaskTreeView::waitTaskFinished(os);
    GTUtilsNotifications::checkNotificationReportText(os, { "Failed to download",
                                                            "https://www.ncbi.nlm.nih.gov/nucleotide/NC_001363?report=genbank"});
}

}  // namespace GUITest_common_scenarios_project_remote_request
}  // namespace U2
