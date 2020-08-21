``` mermaid

classDiagram

    class Mole{
        + uint8_t DisplayTime
        + uint8_t enum State
        + OutObHole()
        + DoNothing()
        + BackToHole()
        + Attacked()
        - mole_setState(uint8_t enum) 状態遷移処理
        - mole_reduceDisplayTime() 表示時間の減少
        - mole_determineaApearance() モグラの出現を判定する

    }

    class Score{
        + uint8_t Score
    }

    class Time{
        - uint8_t Time
    }

    class Input{
        
    }


```