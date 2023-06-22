using System.Collections.Generic;
using System.Linq;
using System.Windows.Input;

namespace ChessBoard
{
    public class MainViewModel : NotifyPropertyChanged
    {
        private Board _board = new Board();
        private ICommand _newGameCommand;
        private ICommand _clearCommand;
        private ICommand _cellCommand;

        public IEnumerable<char> Numbers => "54321";
        public IEnumerable<char> Letters => "ABCDE";

        public Board Board 
        {
            get => _board;
            set
            {
                _board = value;
                OnPropertyChanged();
            }
        }

        public ICommand NewGameCommand => _newGameCommand ??= new RelayCommand(parameter => 
        {
            SetupBoard();
        });

        public ICommand ClearCommand => _clearCommand ??= new RelayCommand(parameter =>
        {
            Board = new Board();
        });

        public ICommand CellCommand => _cellCommand ??= new RelayCommand(parameter =>
        {
            Cell cell = (Cell)parameter;
            Cell activeCell = Board.FirstOrDefault(x => x.Active);
            if (cell.State != State.Empty)
            {
                if (!cell.Active && activeCell != null)
                    activeCell.Active = false;
                cell.Active = !cell.Active;
            }
            else if (activeCell != null)
            {
                activeCell.Active = false;
                cell.State = activeCell.State;
                activeCell.State = State.Empty;
            }
        }, parameter => parameter is Cell cell && (Board.Any(x => x.Active) || cell.State != State.Empty));

        private void SetupBoard()
        {
            Board board = new Board();
            board[0, 1] = State.BlackPawn;
            board[0, 3] = State.BlackPawn;
            board[1, 0] = State.BlackPawn;
            board[1, 2] = State.BlackPawn;
            board[1, 4] = State.BlackPawn;



            board[3, 0] = State.WhitePawn;
            board[3, 2] = State.WhitePawn;
            board[3, 4] = State.WhitePawn;
            board[4, 1] = State.WhitePawn;
            board[4, 3] = State.WhitePawn;
            Board = board;
        }

        public MainViewModel()
        {
        }
    }
}