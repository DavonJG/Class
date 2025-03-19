-- LCvm.hs 
-- Davon Grant
--   Version 8.2 (Sun Mar  6 14:50:26 EST 2016)

module LCvm where

import Data.Word          (Word8)
import Data.Array.Unboxed (UArray,listArray,(!),(//))
import LC2                (Location,Wrd,boolToWrd)

------------------------------------------------------------------------
-- Contents (most of which you can ignore)
--   Memory banks: types and operations on
--                 length-256 arrays of 8-bit unsigned ints
--    * empty: an empty (all 0) bank
--    * set:   set the value of a location in a bank
--    * load:  load a list of ints into a bank
--   Op codes
--    * OpCode(HALT, PUSH, ..., RET): the VM op codes
--    * wrdToOp: translates an op code number to an OpCode
--    * opToWrd: translates an OpCode to an op code number
--    * halt, push, ..., ret: names for op-code numbers
--   Assembly code
--    * AsmCode: data structure for assembly code
--    * assemble: translate a list of assembly instructions to machine code
--    * atrans: translate a single assembly instruction to machine code
--    * prnAsm: pretty prints an assembly program
--    * prnInst, formatWrd: utilities for prnAsm
--    * disInstr: disassembles machine code to assembly
--    * codeLen: computes the length (in machine words) of
--               an assembly program
--    * instrLen: utility for codeLen
--   The VM
--    * Config: type for vm-configurations
--    * startConfig: the starting vm-configuration
--    * step: do one step of the vm
--    * halting: test if a config is halting
--    * run: run a vm-program from a given configuration
--           returns the final config
--    * run': run a vm-program from a given configuration
--           returns a trace
--   VM testing utilities
--    * showRun: assemble, load, and run the assembly program
--               prints the entire trace
--    * stepRun: assemble, load, and run the assembly program
--               steps you through the trace
--    * stepRun': same as above, but it also prints the assembly program
--    * prn: pretty printing a bank
--    * fact4: an example assembly program for computing 4!.
--   Homework 7 tests
--    * negTest, ... 

------------------------------------------------------------------------


fixMe fun = error $ "fix me: " ++ fun

---------------------------------------------------------------------------
-- Memory banks
---------------------------------------------------------------------------
-- Bank = an array of 8-bit unsigned ints, indexed by 8-bit unsigned ints
-- bk!i = the bank bk's value at index i
type Bank = UArray Location Wrd

empty :: Bank
-- an empty (all 0's) memory bank
empty = listArray (minBound,maxBound) [0,0..]

set :: Bank -> Location -> Wrd -> Bank
-- (set b i c) = the result of setting b[i] to c.
set b i c = b // [(i,c)]

load :: Bank -> [Wrd] -> Bank
-- (load bnk vals) == the result of loading the vals sequentially into bnk
--   starting with location 0
load bnk vals = bnk // (zip [0..] vals)

---------------------------------------------------------------------------
-- The Op Codes 
---------------------------------------------------------------------------

data OpCode = HALT 
            | PUSH | POP  | DUP   | FETCH | STORE
            | IADD | ISUB | IMULT | ILT   | NEG | NAND
            | JMP  | JZ   | JNZ
            | CALL | RET
              deriving (Show,Eq,Enum,Bounded)

wrdToOp :: Wrd -> OpCode
-- translate from opcode number to an OpCode.  E.g.: (wrdToOp 5) ~> STORE
wrdToOp = toEnum.fromEnum

opToWrd :: OpCode -> Wrd
-- translate from OpCode to an opcode number.  E.g.: (opToWrd STORE) ~> 5
opToWrd = toEnum.fromEnum

-- Assign names to the op-code numbers.  E.g. store == 5
[halt,push,pop,dup,fetch,store,
     iadd,isub,imult,ilt,neg,nand,jmp,jz,jnz,call,ret] 
    = map opToWrd [HALT,PUSH,POP,DUP,FETCH,STORE,
                   IADD,ISUB,IMULT,ILT,NEG,NAND,JMP,JZ,JNZ,CALL,RET] 

---------------------------------------------------------------------------
-- Assembly code
---------------------------------------------------------------------------
data AsmCode = Halt 
             | Push Wrd | Pop | Dup | Fetch Wrd | Store Wrd
             | Iadd | Isub | Imult | Ilt | Neg | Nand
             | Jmp Wrd | Jz Wrd | Jnz Wrd
             | Call Wrd | Ret 
               deriving (Show)

assemble :: [AsmCode] -> [Wrd]
-- Translate a list of assembly instructions into machine code, e.g.,
--  assemble [Push 100,Push 20,Isub] = [1,100,1,20,7]
assemble instrs = concatMap atrans instrs

atrans :: AsmCode -> [Wrd]
-- Translate a single assembly instruction to machine code
--    E.g.: atrans (Store 11) ~> [5,11]
atrans Halt      = [halt]
atrans (Push w)  = [push,w]
atrans Pop       = [pop]
atrans Dup       = [dup]
atrans (Fetch w) = [fetch,w]
atrans (Store w) = [store,w]
atrans Iadd      = [iadd]
atrans Isub      = [isub]
atrans Imult     = [imult]
atrans Ilt       = [ilt]
atrans Neg       = [neg]
atrans Nand      = [nand]
atrans (Jmp w)   = [jmp,w]
atrans (Jz w)    = [jz,w]
atrans (Jnz w)   = [jnz,w]
atrans (Call w)  = [call,w]
atrans Ret       = [ret]

prnAsm :: [AsmCode] -> IO ()
-- pretty prints an assembly program.  Try: (prnAsm fact4)
prnAsm instrs = mapM_ prnInstr (label 0 instrs)
    where
      label :: Wrd -> [AsmCode] -> [(Wrd,AsmCode)]
      label pc []      = []
      label pc (i:is)  =  (pc,i):label (pc+(instrLen i)) is

prnInstr :: (Wrd,AsmCode) -> IO ()
-- (prnInstr (n,instr)) prints assembly instruction instr together
-- with its location n
prnInstr (n,instr) = do { putStr ((formatWrd n)++": "); print instr } 

formatWrd :: Wrd -> String
-- I didn't feel like using printf. 
formatWrd n 
    = take (3 - (floor $ (log $ fromIntegral n)/(log 10))) "   " ++ show n


disInstr :: Wrd -> Wrd -> AsmCode
-- (disInstr op arg) constructs the assembly instruction for op
-- (with the argument arg if needed)
disInstr op arg = case wrdToOp op of
                    HALT  -> Halt
                    PUSH  -> Push arg
                    POP   -> Pop
                    DUP   -> Dup
                    FETCH -> Fetch arg
                    STORE -> Store arg
                    IADD  -> Iadd
                    ISUB  -> Isub
                    IMULT -> Imult
                    ILT   -> Ilt
                    NEG   -> Neg
                    NAND  -> Nand
                    JMP   -> Jmp arg
                    JZ    -> Jz arg
                    JNZ   -> Jnz arg
                    CALL  -> Call arg
                    RET   -> Ret

codeLen :: [AsmCode] -> Wrd
-- (codeLen is) = the length of a sequence of assemble instructions
--    when loaded into memory.
-- E.g. codeLen [Pop] = 1, codeLen [Push 8] = 2, codeLen [Pop,Push 8] = 3.
codeLen is = sum [instrLen instr | instr <- is]

instrLen :: AsmCode -> Wrd
-- (instrLen instr) = the length of an assembly instruciton.
--   E.g., instrLen Pop = 1, instrLen (Push 8) = 2
instrLen instr = fromIntegral (length (atrans instr))


---------------------------------------------------------------------------
-- The VM
---------------------------------------------------------------------------
-- a configuration consists of 
--   1. a program counter (ptr to the current instruction)
--   2. a stack pointer (1+the top of the stack)
--   3. a Bank containing the stack
--   4. a Bank containing the registers
-- The object code remains fixed in a run, so it is not part of 
-- the configuration.

type Config = (Wrd,Wrd,Bank,Bank)

startConfig :: Config 
startConfig = (0,0,empty,empty)

step :: Bank -> Config -> Config
-- One step of the VM, that is, 
--   (step obj c) = the next configuration of the machine
step obj (pc,sp,stk,regs) =
    let arg = obj!(pc+1)  -- the word following the current instr
        top = stk!(sp-1)  -- the top of the stack
        nxt = stk!(sp-2)  -- the elem of the stack just below the top
     in 
      case wrdToOp (obj!pc) of 
        HALT  -> error "no next step!"
        PUSH  -> (pc+2, sp+1, set stk sp arg             , regs)
        POP   -> (pc+1, sp-1, stk                        , regs)
-- For Homework 7
        DUP   -> (pc+1, sp', stk'                        , regs)
            where sp' = if sp==0 then 0 else sp+1
                  stk' = if sp==0 then stk else (set stk sp top)
        FETCH -> (pc+2, sp+1, set stk sp (regs!arg)      , regs)
        STORE -> (pc+2, sp  , stk                        , set regs arg top)
        IADD  -> (pc+1, sp-1, set stk (sp-2) (nxt+top)   , regs)
        ISUB  -> (pc+1, sp-1, set stk (sp-2) (nxt-top)   , regs)
        IMULT -> (pc+1, sp-1, set stk (sp-2) (nxt*top)   , regs)
        ILT   -> (pc+1, sp-1, set stk (sp-2) b           , regs)
            where b = boolToWrd (nxt<top)
-- For Homework 7
        NEG   -> (pc+1, sp, set stk (sp-1) (-top)        , regs)
-- For Homework 7
        NAND  -> (pc+1, sp-1, set stk (sp-2) v           , regs)
            where v = if (top==0 || nxt==0) then 1 else 0
        JMP   -> (pc' , sp  , stk                        , regs)
            where pc' = pc+arg+1
        JZ    -> (pc' , sp-1, stk                        , regs)
            where pc' = if top==0 then (pc+arg+1) else (pc+2)
        JNZ   -> (pc' , sp-1, stk                        , regs)
            where pc' = if top/=0 then (pc+arg+1) else (pc+2)
-- For Homework 7
        CALL  -> (arg, sp+1, set stk sp (pc+2)           , regs)
-- For Homework 7
        RET   -> (top, sp-1, stk                         , regs)

halting :: Bank -> Config -> Bool
 -- (halting obj c) tests if c is a halting configuration
halting obj (pc,_,_,_) = (halt == obj!pc)

run  :: Bank -> Config -> Config
-- (run obj cfg) = run obj on cfg and return the final config
run  obj cfg = if halting obj cfg 
                  then cfg   
                  else run obj (step obj cfg)

run' :: Bank -> Config -> [Config]
-- (run' obj cfg) = run obj on cfg and return the course of configs
run' obj cfg = if halting obj cfg 
                  then [cfg] 
                  else cfg:run' obj (step obj cfg)

---------------------------------------------------------------------------
-- Utilities: printing VM runs
---------------------------------------------------------------------------

showRun :: [AsmCode] -> IO ()
-- showRun ap = assemble, load, and go (i.e., run the assembly program)
showRun ap = mapM_ (prn obj) trace   -- print the result
    where
      mc    = assemble ap          -- assem.~prog -> machine code
      obj   = load empty mc        -- load the machine code
      trace = run' obj startConfig -- a trace of the run

stepRun :: [AsmCode] -> IO ()
-- stepRun ap = assemble, load, and go (i.e., run the assembly program)
--                 and step through the run
stepRun ap = mapM_ showStep (zip [1..] trace)
    where
      mc    = assemble ap          -- assem.~prog -> machine code
      obj   = load empty mc        -- load the machine code
      trace = run' obj startConfig -- a trace of the run
      showStep (n,c)               -- print a numbered config and read a char
            = do { putStr "Step "
                 ; print n
                 ; prn obj c
                 ; putStr "\t<tap return>"
                 ; getChar
                 }

stepRun' :: [AsmCode] -> IO ()
-- stepRun' ap = same as stepRun, but it prints the assembly program
--   before the run
stepRun' ap = do { putStrLn "A run of:"
                 ; prnAsm ap
                 ; putStr "\n"
                 ; stepRun ap
                 }

prn :: Bank -> Config -> IO ()
-- (prn obj config) prints the current instruction + configuration
prn obj (pc,sp,stk,regs) = 
    do { prnInstr (pc,disInstr (obj!pc) (obj!(pc+1)))
       ; putStr "Stack:     "
       ; print [stk!(j-1) | j <- [1..sp]]
       ; putStr "Regs(!=0): "
       ; mapM_ putStr [reg i++"="++show (regs!i)++" " 
                           | i<-[minBound..maxBound], regs!i/=0]
       {-- ; putStrLn "\n" --}
       }
    where 
      reg i = 'x':show i


-- Example: one way of computing 4!
fact4 = [Push 4, Store 0, Pop, Push 1, Store 1, Pop, Push 1, Fetch 0,
         Push 0, Isub, Push 1, Ilt, Isub, Jz 19, Fetch 1, Fetch 0, Imult,
         Store 1, Pop, Fetch 0, Push 1, Isub, Store 0, Pop, Jmp 226, Halt]              


---------------------------------------------------------------------------
-- HOMEWORK 7 TESTS
---------------------------------------------------------------------------

-- (negTest k) 
--   When run, (-k) `mod` 256 should be at the top of the stack.
-- Try: (incTest 0) and (incTest 255)
negTest :: Wrd -> IO ()
negTest k = stepRun [Push k,Neg,Halt]

-- (nandTest j k) 
--   When j==0 or k==0, the last config. should have 1 at the top of the stack.
--   Otherwise, 0 should be the top of the stack.
-- Try: (showRun (nandTest 1 1)) and (showRun (nandTest 0 0))
nandTest :: Wrd -> Wrd -> IO ()
nandTest j k = stepRun [Push j,Push k,Nand,Halt]

-- (dupTest ns)
--   When ns==[], the final stack should be empty
--   When ns==[n0,n1,...,nk], the final stack should be ns++[nk]
dupTest :: [Wrd] -> IO ()
dupTest ns = stepRun ([Push n | n<-ns]++[Dup,Halt])

-- callRetTest k
--   when 0 <= k <= 245, this should run in 7 steps and halt
--      with x0=10 and 20 at the top of the stack.
--   when 246 <= k <= 255, various bad things happen (which is OK)
callRetTest :: Wrd -> IO ()
callRetTest k = stepRun ap
    where ap = [Call (k+5),Push 20,Halt]
                 ++(replicate (fromEnum k) Halt)
                 ++ [Push 10,Store 0,Pop,Ret]

-- another way of computing 4! using Dup, Call, and Ret.
--   This should take 67 steps and end with an empty stack and x1=24.
fact4' = [Push 4,  Store 0, Pop, Call 8, Halt,
          Fetch 0, Jnz 7, Push 1, Store 1, Pop, Ret,
          Fetch 0, Dup, Push 1, Isub, Store 0, Pop, Call 8, 
          Fetch 1, Imult, Store 1, Pop, Ret] 

                    
