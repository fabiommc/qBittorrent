/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2018  Vladimir Golovnev <glassez@yandex.ru>
 * Copyright (C) 2006  Christophe Dumez <chris@qbittorrent.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 */

#pragma once

#include <QWidget>

#define ENGINE_URL_COLUMN 4
#define URL_COLUMN 5

class QLabel;
class QModelIndex;
class QHeaderView;
class QStandardItem;
class QStandardItemModel;
class QVBoxLayout;

template <typename T> class CachedSettingValue;

class SearchHandler;
class SearchSortModel;
class SearchListDelegate;
struct SearchResult;

namespace Ui
{
    class SearchTab;
}

class SearchTab : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(SearchTab)

public:
    enum class NameFilteringMode
    {
        Everywhere,
        OnlyNames
    };
    Q_ENUM(NameFilteringMode)

    enum class Status
    {
        Ongoing,
        Finished,
        Error,
        Aborted,
        NoResults
    };

    explicit SearchTab(SearchHandler *searchHandler, QWidget *parent = nullptr);
    ~SearchTab() override;

    Status status() const;
    int visibleResultsCount() const;

    void cancelSearch();

    void downloadTorrents();
    void openTorrentPages();
    void copyTorrentURLs();

signals:
    void resultsCountUpdated();
    void statusChanged();

private:
    void loadSettings();
    void saveSettings() const;
    void updateFilter();
    void displayToggleColumnsMenu(const QPoint&);
    void onItemDoubleClicked(const QModelIndex &index);
    void searchFinished(bool cancelled);
    void searchFailed();
    void appendSearchResults(const QList<SearchResult> &results);
    void updateResultsCount();
    void setStatus(Status value);
    void downloadTorrent(const QModelIndex &rowIndex);
    void addTorrentToSession(const QString &source);
    void fillFilterComboBoxes();
    NameFilteringMode filteringMode() const;
    QHeaderView *header() const;
    void setRowColor(int row, const QColor &color);

    static QString statusText(Status st);
    static CachedSettingValue<NameFilteringMode>& nameFilteringModeSetting();

    Ui::SearchTab *m_ui;
    SearchHandler *m_searchHandler;
    QStandardItemModel *m_searchListModel;
    SearchSortModel *m_proxyModel;
    SearchListDelegate *m_searchDelegate;
    Status m_status = Status::Ongoing;
    bool m_noSearchResults = true;
};

Q_DECLARE_METATYPE(SearchTab::NameFilteringMode)
