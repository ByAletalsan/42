import { changeSectionGameLocal } from '../script.js';

// Funcion para crear partida de torneo 1v1 Local
// p1 -> player1 of game, p2 -> player2 of game, (fp1, fp2) -> finalists of tournament
export const createGame = (p1, p2, player1, player2, player3, player4, fp1=null, fp2=null) => {
    const scientist = ['charles-darwin.gif', 'curie.gif', 'hawking.gif', 'newton.gif', 'einstein.gif', 'pitagoras.gif'];
    document.getElementById('nickP1').innerText = p1.nick;
    document.getElementById('nickP2').innerText = p2.nick;
    document.getElementById('charPlayer1').src = 'gif/' + scientist[p1.scientist];
    document.getElementById('charPlayer2').src = 'gif/flop/' + scientist[p2.scientist];
    const data_game = JSON.stringify({'player1': p1.nick, 'spell_p1': p1.scientist, 'player2': p2.nick, 'spell_p2': p2.scientist, 'tour': [p1, p2]});
    localStorage.setItem('data-game', data_game);
    changeSectionGameLocal(player1, player2, player3, player4, fp1, fp2);
};

// Funcion para inicializar el torneo 1v1 Local
export function tournamentLocal()
{
    const scientist_selected = [0, 1, 2, 3, 4, 5];

    const Players = class {
        constructor(nick, scientist) {
            this.nick = nick;
            this.scientist = scientist;
        }
    };

    const getNick = (player) => {
        let nick = prompt(`Nick from ${player}`);
        while (nick != null && (nick == '' || nick.length > 7))
            nick = prompt(`Nick from ${player}`);
        return nick;
    };

    const getScientist = () => {
        const index = Math.floor(Math.random() * scientist_selected.length)
        const scientist = scientist_selected[index];
        scientist_selected.splice(index, 1);
        return scientist;
    };

    const player1 = new Players(getNick('Player1'), getScientist());
    if (!player1.nick) return;
    const player2 = new Players(getNick('Player2'), getScientist());
    if (!player2.nick) return;
    const player3 = new Players(getNick('Player3'), getScientist());
    if (!player3.nick) return;
    const player4 = new Players(getNick('Player4'), getScientist());
    if (!player4.nick) return;

    //Tournament
    const data_tour_1v1 = {
        'player1': player1,
        'player2': player2,
        'player3': player3,
        'player4': player4,
        'win1': null,
        'win2': null
    };

    localStorage.setItem('data-tour-1v1', JSON.stringify(data_tour_1v1));
    createGame(player1, player2, player1, player2, player3, player4);

    return;
};