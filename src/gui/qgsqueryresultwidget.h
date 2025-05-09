/***************************************************************************
  qgsqueryresultwidget.h - QgsQueryResultWidget

 ---------------------
 begin                : 14.1.2021
 copyright            : (C) 2021 by elpaso
 email                : elpaso@itopen.it
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSQUERYRESULTWIDGET_H
#define QGSQUERYRESULTWIDGET_H

#include "qgis_gui.h"
#include "qgis_sip.h"
#include "ui_qgsqueryresultwidgetbase.h"
#include "ui_qgsqueryresultpanelwidgetbase.h"
#include "qgsabstractdatabaseproviderconnection.h"
#include "qgsqueryresultmodel.h"
#include "qgsfeedback.h"
#include "qgssettingstree.h"

#include <QWidget>
#include <QThread>
#include <QtConcurrent>
#include <QStyledItemDelegate>
#include <QDialog>
#include <QMainWindow>

class QgsCodeEditorWidget;
class QgsCodeEditorSQL;
class QgsQueryResultPanelWidget;
class QgsDatabaseQueryHistoryWidget;

///@cond private

#ifndef SIP_RUN

/**
 * The QgsQueryResultItemDelegate class shows results truncated to 255 characters and using current locale
 */
class GUI_EXPORT QgsQueryResultItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    // QStyledItemDelegate interface
  public:
    explicit QgsQueryResultItemDelegate( QObject *parent = nullptr );

    QString displayText( const QVariant &value, const QLocale &locale ) const override;
};

/**
 * The QgsConnectionsApiFetcher class fetches tokens (schema, table and field names) of a connection from a separate thread.
 * WARNING: this class is an implementation detail and it is not part of public API!
 */
class GUI_EXPORT QgsConnectionsApiFetcher : public QObject
{
    Q_OBJECT

  public:
    //! Constructs a result fetcher from connection with the specified \a uri and \a providerKey.
    QgsConnectionsApiFetcher( const QString &uri, const QString &providerKey )
      : mUri( uri )
      , mProviderKey( providerKey )
    {}

    //! Start fetching
    void fetchTokens();

    //! Stop fetching
    void stopFetching();

  signals:

    //!! Emitted when \a newTokens have been fetched.
    void tokensReady( const QStringList &newTokens );

    //! Emitted when fetching of tokes has finished or has been interrupted.
    void fetchingFinished();

  private:
    QString mUri;
    QString mProviderKey;
    QAtomicInt mStopFetching = 0;
    std::unique_ptr<QgsFeedback> mFeedback;
};

#endif

///@endcond private

/**
 * \ingroup gui
 * \brief A widget which allows users to enter and run an SQL query on a
 * DB connection (an instance of QgsAbstractDatabaseProviderConnection).
 *
 * Query results are displayed in a table view.
 * Query execution and result fetching can be interrupted by pressing the "Stop" push button.
 *
 * The widget supports a few QueryWidgetMode modes that pre-configure the widget appearance to
 * be used in different contexts like when updating the SQL of an existing query layer.
 *
 * \note the ownership of the connection is transferred to the widget.
 *
 * \since QGIS 3.22
 */
class GUI_EXPORT QgsQueryResultWidget : public QWidget, private Ui::QgsQueryResultWidgetBase
{
    Q_OBJECT

  public:
#ifndef SIP_RUN
    ///@cond PRIVATE
    static inline QgsSettingsTreeNode *sTreeSqlQueries = QgsSettingsTree::sTreeGui->createChildNode( QStringLiteral( "sql-queries" ) );
    static const QgsSettingsEntryString *settingLastSourceFolder;
///@endcond PRIVATE
#endif

    /**
     * \brief The QueryWidgetMode enum represents various modes for the widget appearance.
     */
    enum class QueryWidgetMode : int SIP_ENUM_BASETYPE( IntFlag )
    {
      SqlQueryMode = 1 << 0,         //!< Defaults widget mode for SQL execution and SQL query layer creation.
      QueryLayerUpdateMode = 1 << 1, //!< SQL query layer update mode: the create SQL layer button is renamed to 'Update' and the SQL layer creation group box is expanded.
    };
    Q_ENUM( QueryWidgetMode )

    /**
     * Creates a QgsQueryResultWidget with the given \a connection, ownership is transferred to the widget.
     */
    QgsQueryResultWidget( QWidget *parent = nullptr, QgsAbstractDatabaseProviderConnection *connection SIP_TRANSFER = nullptr );

    virtual ~QgsQueryResultWidget();

    /**
     * Initializes the widget from \a options.
     */
    void setSqlVectorLayerOptions( const QgsAbstractDatabaseProviderConnection::SqlVectorLayerOptions &options );

    /**
     * Sets the widget mode to \a widgetMode, default is SqlQueryMode.
     */
    void setWidgetMode( QueryWidgetMode widgetMode );

    /**
     * Sets the connection to \a connection, ownership is transferred to the widget.
     */
    void setConnection( QgsAbstractDatabaseProviderConnection *connection SIP_TRANSFER );

    /**
     * Convenience method to set the SQL editor text to \a sql.
     */
    void setQuery( const QString &sql );

    SIP_SKIP bool promptUnsavedChanges();

  public slots:

    /**
     * Displays a message with \a text \a title and \a level in the widget's message bar.
     */
    void notify( const QString &title, const QString &text, Qgis::MessageLevel level = Qgis::MessageLevel::Info );

    /**
     * Starts executing the query.
     */
    void executeQuery();

    /**
      * Hides the result table and shows the error \a title and \a message in the message bar or
      * in the SQL error panel is \a isSqlError is set.
      */
    void showError( const QString &title, const QString &message, bool isSqlError = false );

    /**
     * Triggered when the threaded API fetcher has new \a tokens to add.
     *
     * \deprecated QGIS 3.44, has no effect
     */
    Q_DECL_DEPRECATED void tokensReady( const QStringList &tokens ) SIP_DEPRECATED;

    /**
     * Copies the query results to the clipboard, as a formatted table.
     *
     * \since QGIS 3.32
     */
    void copyResults();

    /**
     * Copies a range of the query results to the clipboard, as a formatted table.
     *
     * \since QGIS 3.32
     */
    void copyResults( int fromRow, int toRow, int fromColumn, int toColumn );

  signals:

    /**
     * Emitted when a new vector SQL (query) layer must be created.
     * \param providerKey name of the data provider
     * \param connectionUri the connection URI as returned by QgsAbstractProviderConnection::uri()
     * \param options
     */
    void createSqlVectorLayer( const QString &providerKey, const QString &connectionUri, const QgsAbstractDatabaseProviderConnection::SqlVectorLayerOptions &options );

    /**
     * Emitted when the first batch of results has been fetched.
     * \note If the query returns no results this signal is not emitted.
     */
    void firstResultBatchFetched();

    SIP_SKIP void requestDialogTitleUpdate( const QString &filename );

  private slots:

    /**
     * Updates buttons status.
     */
    void updateButtons();

    void openQuery();
    void saveQuery( bool saveAs );
    void setHasChanged( bool hasChanged );
    void populatePresetQueryMenu();
    void showHistoryPanel( bool show );

  private:
    QgsQueryResultPanelWidget *mQueryWidget = nullptr;
    QPointer< QgsDatabaseQueryHistoryWidget > mHistoryWidget;

    QMenu *mPresetQueryMenu = nullptr;

    bool mHasChangedFileContents = false;

    void updateDialogTitle();
    void storeCurrentQuery( Qgis::QueryStorageBackend backend );

    friend class TestQgsQueryResultWidget;
};

#ifndef SIP_RUN

/**
 * \ingroup gui
 * \brief A panel widget which allows users to enter and run an SQL query on a
 * DB connection (an instance of QgsAbstractDatabaseProviderConnection).
 *
 * \note the ownership of the connection is transferred to the widget.
 *
 * \see QgsQueryResultWidget
 *
 * \since QGIS 3.22
 */
class GUI_EXPORT QgsQueryResultPanelWidget : public QgsPanelWidget, private Ui::QgsQueryResultPanelWidgetBase
{
    Q_OBJECT

  public:
    /**
     * Creates a QgsQueryResultPanelWidget with the given \a connection, ownership is transferred to the widget.
     */
    QgsQueryResultPanelWidget( QWidget *parent = nullptr, QgsAbstractDatabaseProviderConnection *connection SIP_TRANSFER = nullptr );

    ~QgsQueryResultPanelWidget() override;

    /**
     * Returns the widget's SQL editor.
     */
    QgsCodeEditorSQL *sqlEditor();

    /**
     * Returns the widget's code editor widget.
     */
    QgsCodeEditorWidget *codeEditorWidget();

    /**
     * Initializes the widget from \a options.
     */
    void setSqlVectorLayerOptions( const QgsAbstractDatabaseProviderConnection::SqlVectorLayerOptions &options );

    /**
     * Sets the widget mode to \a widgetMode, default is SqlQueryMode.
     */
    void setWidgetMode( QgsQueryResultWidget::QueryWidgetMode widgetMode );

    /**
     * Sets the connection to \a connection, ownership is transferred to the widget.
     */
    void setConnection( QgsAbstractDatabaseProviderConnection *connection SIP_TRANSFER );

    /**
     * Convenience method to set the SQL editor text to \a sql.
     */
    void setQuery( const QString &sql );

  public slots:

    /**
     * Displays a message with \a text \a title and \a level in the widget's message bar.
     */
    void notify( const QString &title, const QString &text, Qgis::MessageLevel level = Qgis::MessageLevel::Info );

    /**
     * Starts executing the query.
     */
    void executeQuery();

    /**
      * Hides the result table and shows the error \a title and \a message in the message bar or
      * in the SQL error panel is \a isSqlError is set.
      */
    void showError( const QString &title, const QString &message, bool isSqlError = false );

    /**
     * Triggered when the threaded API fetcher has new \a tokens to add.
     */
    void tokensReady( const QStringList &tokens );

    /**
     * Copies the query results to the clipboard, as a formatted table.
     *
     * \since QGIS 3.32
     */
    void copyResults();

    /**
     * Copies a range of the query results to the clipboard, as a formatted table.
     *
     * \since QGIS 3.32
     */
    void copyResults( int fromRow, int toRow, int fromColumn, int toColumn );

  signals:

    /**
     * Emitted when a new vector SQL (query) layer must be created.
     * \param providerKey name of the data provider
     * \param connectionUri the connection URI as returned by QgsAbstractProviderConnection::uri()
     * \param options
     */
    void createSqlVectorLayer( const QString &providerKey, const QString &connectionUri, const QgsAbstractDatabaseProviderConnection::SqlVectorLayerOptions &options );

    /**
     * Emitted when the first batch of results has been fetched.
     * \note If the query returns no results this signal is not emitted.
     */
    void firstResultBatchFetched();

  private slots:

    /**
     * Updates buttons status.
     */
    void updateButtons();

    void showCellContextMenu( QPoint point );
    void copySelection();

  private:
    QgsCodeEditorWidget *mCodeEditorWidget = nullptr;
    QgsCodeEditorSQL *mSqlEditor = nullptr;

    std::unique_ptr<QgsAbstractDatabaseProviderConnection> mConnection;
    std::unique_ptr<QgsQueryResultModel> mModel;
    std::unique_ptr<QgsFeedback> mFeedback;

    QPointer<QgsConnectionsApiFetcher> mApiFetcher;

    bool mWasCanceled = false;
    mutable QgsAbstractDatabaseProviderConnection::SqlVectorLayerOptions mSqlVectorLayerOptions;
    bool mFirstRowFetched = false;
    QFutureWatcher<QgsAbstractDatabaseProviderConnection::QueryResult> mQueryResultWatcher;
    QString mSqlErrorMessage;
    long long mActualRowCount = -1;
    long long mFetchedRowsBatchCount = 0;
    QgsQueryResultWidget::QueryWidgetMode mQueryWidgetMode = QgsQueryResultWidget::QueryWidgetMode::SqlQueryMode;
    long long mCurrentHistoryEntryId = -1;

    /**
     * Updates SQL layer columns.
     */
    void updateSqlLayerColumns();

    /**
     * Cancel and wait for finish.
     */
    void cancelRunningQuery();

    /**
     * Cancel API fetching.
     */
    void cancelApiFetcher();

    /**
     * Starts the model population after initial query run.
     */
    void startFetching();

    /**
     * Returns the sqlVectorLayerOptions
     */
    QgsAbstractDatabaseProviderConnection::SqlVectorLayerOptions sqlVectorLayerOptions() const;

    void storeCurrentQuery( Qgis::QueryStorageBackend backend );

    friend class TestQgsQueryResultWidget;
    friend class QgsQueryResultWidget;
};
#endif

/**
 * \ingroup gui
 * \brief A dialog which allows users to enter and run an SQL query on a
 * DB connection (an instance of QgsAbstractDatabaseProviderConnection).
 *
 * \note the ownership of the connection is transferred to the dialog.
 *
 * \see QgsQueryResultWidget
 *
 * \since QGIS 3.44
 */
class GUI_EXPORT QgsQueryResultDialog : public QDialog
{
    Q_OBJECT

  public:
    /**
     * Constructor for QgsQueryResultDialog.
     *
     * Ownership of the \a connection is transferred to the dialog.
     */
    QgsQueryResultDialog( QgsAbstractDatabaseProviderConnection *connection SIP_TRANSFER = nullptr, QWidget *parent = nullptr );

    /**
     * Returns the QgsQueryResultWidget shown in the dialog.
     */
    QgsQueryResultWidget *resultWidget() { return mWidget; }

    void closeEvent( QCloseEvent *event ) override;

  private:
    QgsQueryResultWidget *mWidget = nullptr;
};

/**
 * \ingroup gui
 * \brief A main window which allows users to enter and run an SQL query on a
 * DB connection (an instance of QgsAbstractDatabaseProviderConnection).
 *
 * \note the ownership of the connection is transferred to the window.
 *
 * \see QgsQueryResultWidget
 *
 * \since QGIS 3.44
 */
class GUI_EXPORT QgsQueryResultMainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    /**
     * Constructor for QgsQueryResultMainWindow.
     *
     * Ownership of the \a connection is transferred to the window.
     */
    QgsQueryResultMainWindow( QgsAbstractDatabaseProviderConnection *connection SIP_TRANSFER = nullptr, const QString &identifierName = QString() );

    /**
     * Returns the QgsQueryResultWidget shown in the window.
     */
    QgsQueryResultWidget *resultWidget() { return mWidget; }

    void closeEvent( QCloseEvent *event ) override;

  private:
    QgsQueryResultWidget *mWidget = nullptr;
    QString mIdentifierName;

    void updateWindowTitle( const QString &fileName );
};

#endif // QGSQUERYRESULTWIDGET_H
