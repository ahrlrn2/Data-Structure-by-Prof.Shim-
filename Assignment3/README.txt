Card Game Solitaire (2020-18169 김상민)

-Compiling environment
OS: Windows 11
Compiler: g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
Editor: Visual Studio Code


-How to read output

Solitaire의 실행 결과를 나타내는 output.txt는 게임 시작 시,  "Let's start a game!! Random seed is 0"와 같이 게임이 시작한다는 문구와 함께 사용한 random seed를 출력한다. 게임이 끝날 때에는 "Final Status"라는 문구와 함께 최종 상태를 나타낸 후, "Game End!! Your final score is -12"와 같이 게임이 끝났다는 문구와 최종 점수를 알려준다.

게임의 시작, 끝과 카드의 이동이 일어날 때, 카드의 이동에 대한 설명, Score, 카드들의 전체적인 상태를 나타내는 Piles를 출력한다. Score는 각 이동이 일어난 후의 점수를 뜻하며 Piles를 이동이 일어난 후 카드들의 배열 상태를 뜻한다.


카드의 이동에 관한 설명은 "1: ♦A moved from playing pile #3 to output pile #1"과 같이 몇 번째 이동인지와 함께 카드의 이동을 구체적으로 출력한다.

Stock, waste pile, output pile, playing pile은 각각 Stock, Waste, Output1~Output4, Playing1~Playing7로 출력된다. "--"는 카드가 뒤집혀져 있다는 뜻이고 ♦A와 같이 카드의 문양과 수 또는 알파벳이 같이 출력된 경우는 카드가 공개된 경우다. 또한 Playing pile은 비어 있는 경우, output 출력 시 비어 있다는 것이 눈에 잘 띄지만 stock, waste pile, output pile은 눈에 잘 띄지 않으므로 해당 pile들은 비어 있을 때, "empty"가 출력되도록 했다.


Ex)

Let's start a game!! Random seed is 0

Score: -52
Piles:
Stock     Waste          Output1     Output2     Output3     Output4
 --       empty          empty       empty       empty       empty       

Playing1     Playing2     Playing3     Playing4     Playing5     Playing6     Playing7
   ♥K           --           --           --           --           --           --        
                ♠K           --           --           --           --           --        
                             ♦A           --           --           --           --        
                                          ♠7           --           --           --        
                                                       ♣5           --           --        
                                                                    ♣4           --        
                                                                                 ♠2        

---------------------------------------------------------------------------------------------
1: ♦A moved from playing pile #3 to output pile #1
Score: -47
Piles:
Stock     Waste          Output1     Output2     Output3     Output4
 --       empty            ♦A        empty       empty       empty       

Playing1     Playing2     Playing3     Playing4     Playing5     Playing6     Playing7
   ♥K           --           --           --           --           --           --        
                ♠K           ♣J           --           --           --           --        
                                          --           --           --           --        
                                          ♠7           --           --           --        
                                                       ♣5           --           --        
                                                                    ♣4           --        
                                                                                 ♠2        

---------------------------------------------------------------------------------------------

......

---------------------------------------------------------------------------------------------
Final Status
Score: -12
Piles:
Stock     Waste          Output1     Output2     Output3     Output4
empty      ♣7              ♦3          ♥A          ♣2          ♠2        

Playing1     Playing2     Playing3     Playing4     Playing5     Playing6     Playing7
   ♥K           ♦K           --           ♠K           --           --           --        
   ♠Q           ♣Q           ♣J                        --           --           --        
   ♦J                        ♥10                       ♠5           --           --        
   ♣10                       ♣9                                     --           --        
   ♦9                        ♦8                                     --           ♥9        
   ♣8                        ♠7                                     ♣4                     
   ♦7                        ♥6                                                            
   ♣6                        ♣5                                                            
                             ♥4                                                            

---------------------------------------------------------------------------------------------
Game End!! Your final score is -12


