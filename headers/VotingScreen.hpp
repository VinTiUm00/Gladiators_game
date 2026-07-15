#ifndef VOTINGSCREEN_HPP
#define VOTINGSCREEN_HPP

#include <QWidget>
#include <QMap>
#include <QPixmap>
#include <QLabel>

class NetworkManager;
class QPushButton;
class QVBoxLayout;

class VotingScreen : public QWidget {
    Q_OBJECT

public:
    VotingScreen(QWidget* parent = nullptr);
    virtual ~VotingScreen();

    void setNetworkManager(NetworkManager *netMgr) { networkManager = netMgr; }
    void startVoting(const QList<int> &playerIds, const QMap<int, QPixmap> &drawings);
    void updateVoteCount(int playerId, int votes);

signals:
    void exitVotingClicked();
    void voteCasted(int playerId);

private slots:
    void onVoteButtonClicked(int playerId);

private:
    void clearVotingUI();

    NetworkManager *networkManager;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QMap<int, QPushButton *> voteButtons;
    QMap<int, QLabel *> voteCountLabels;
    QList<int> activePlayerIds;
    bool hasVoted;
};

#endif
