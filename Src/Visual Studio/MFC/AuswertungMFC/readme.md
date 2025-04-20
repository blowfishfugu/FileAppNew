## adecc_scholar auf MFC

Diese readme ist Sammlung von Nebengedanken und Konfigurationsinformationen.

Basis vom Projekt bildete ein per VisualStudio-Wizard angelegtes MFC-Desktop-Anwendung-Projekt (targetver wurde entfernt, precompiled header entfernt, temporär und Ausgabepfade angepasst, x86 entfernt)

Orientiert wird sich an der bereits bestehenden AuswertungQt-Anwendung. Darin verwendete Controls sollen durch MFC-Klassen abgebildet werden (sind an sich native win32-controls im RAII-Gewand).

Die verwendete Prozesslogik soll weiterhin in TProcess verweilen, wie bereits in den VCL/FMX-Varianten geschehen.

## Aufbau

### Einsprungpunkt

winmain/main existieren in mfc nicht, main.cpp instanziert von CWinapp abgeleitete Klasse,
die vom Framework implizit aufgerufen wird, winmain ist vorimplementiert von MFC und darin erfolgt
Aufruf von InitInstance und ExitInstance auf der globalen "App"-Klasse.


### Abhaengigkeiten

Submodules wurden als erstes entfernt, und stattdessen ein Verzeichnis höher platziert.

Hintergedanke hierbei, es wird zu massiven Änderungen in den Submodules kommen (myforms wird schrittweise um BUILD_WITH_MFC-defines ergänzt),

daher angenehmer, den Repocontainer direkt in eigenem Ordner und Branch zu verwalten.

(durchaus denkbar, dass die momentan hier vorhandene framework.h in die MyStream.h wandert, mit pch wären wir bereits hier verloren)



### Sourceverwaltung

Zuerst erfolgte clone auf Original-Verzeichnis, danach ein Fork auf github, lokale Anlage eines dev-Branch, dieser soll auf den fork pushen.

Original-verweis fuer fetch weiterhin per upstream-branch erreichbar, dafür ein separater remote der nur fetch kann, push wurde abgetrennt.

Allgemeine Vorbereitungen geschahen per:

```
git checkout -b dev //eigener dev-branch fuer alle Aenderungen
git remote -v //wie siehts aktuell aus
git remote rename origin upstream //adecc-original zu upstream umbenennen
git remote --set-url --push upstream none //push auf original unterbinden
git remote add origin https://github.com/<gitaccount>/<FileAppNew>.git //anbinden an eigenen fork
git push --set-upstream --all origin //upstreams an den fork binden, push/fetch wird darauf erfolgen
git remote -v //look what you have done
git branch --list --all
git status
```

Dies wiederholt fuer jede im FileAppNew enthaltene Abhängigkeit (ausser pugixml.. keine lokalen änderungen geplant)

### props-dateien

"adecc_includes.props" enthaelt Include-Pfade relativ zu $(SolutionDir), 

MyForms.h damit z.B. erreichbar ueber #include <adecc_Scholar/MyForms.h> usw ...

Je nachdem, wo die Bibliotheken liegen, ist dies darin anpassbar (anstatt relativ zum SolutionDir absolut in ganz anderem Ordner, freie Auswahl ;) )

In CMake-Welt wäre das vergleichbar mit einer "find_adecc()", die einem zusätzliche includepfade setzt, props-file ist hartcodiert

## todo

- [x] ueberblick verschaffen, was wird wo verwendet, Abhaengigkeiten ermitteln
- [x] Basisprojekt mit Dialogdesign und Zusatzabhaengigkeiten (includes auf scholar,Tools,FileDlg,pugixml) erstellen
- [x] fw_String = CString (vorraussetzung fuer jegliches Control) : MyFramework_String/MyType_Traits_
- [ ] define BUILD_WITH_MFC unter jeden BUILD_WITH_*-Block haengen, (= error "unbekanntes Framework" behandeln)
- [ ] EMyFramework, alle vorkommnisse behandeln (+mfc)
- [x] EMyFrameworkType, mfc-pendant je typ zuordnen
- [x] TMyWait
- [ ] Find mapping rc-ID aus string
- [ ] TMyForm
- [ ] TMyStream
- [ ] adecc_Tools, wo verwendet? my_line_iterator usw_
- [ ] FileDlg vorerst lokal mitimplementieren, schaut ebenfalls auf obige EMyFrameworkTypes, spaeter als static-lib ins adecc_FileDlg umlagern

## todo, lowprios fuer spaeter

- [ ] _SILENCE_CXX23_UNIX_STREAMS_DEPRECATION_WARNING in preprocessor regeln
- [ ] weitere projekttypen lesen: vcxproj, csproj -> sind sehr verwandt zu cbproj
- [ ] AlignmentStyles MFC-DWord-Defines in struct verpacken (-> Typsicherheit in Aufruf)
- [ ] GetFramework ueber constexpr is_mfc_/is_qt::value usw?_
- [ ] Convert_Size_KiloByte, kandidat fuer constexpr oder template
- [ ] SetListBox: search CaseSensitive, default der CListBox ist insensitive
- [ ] Test: SetPosition( Memo, SetCaretPos)