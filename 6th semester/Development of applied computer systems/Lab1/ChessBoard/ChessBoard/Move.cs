using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChessBoard
{
    internal class Move: IEnumerable<Cell> 
    {
        private readonly Cell[,] _area; // необходимо знать предыдущую выбранную кнопку

        // проверить, можно ли что-то съесть, если да, то съедаем наиболее выгодно (поиск пути с наибольшим весом)
        // если нет, проверяем занятость двух полей перед шашкой, если заняты, то нельзя сходить, иначе подсвечиваем доступные поля (сделать в классе шашки и королевы)
        //
        public State this[int row, int column]
        {
            get => _area[row, column].State;
            set => _area[row, column].State = value;
        }

        /*public bool GetPrevButtonColor(int prevCell)
        {
            if (prevCell)
        }*/

        public IEnumerator<Cell> GetEnumerator()
           => _area.Cast<Cell>().GetEnumerator();

        IEnumerator IEnumerable.GetEnumerator()
            => _area.GetEnumerator();
    }
}
