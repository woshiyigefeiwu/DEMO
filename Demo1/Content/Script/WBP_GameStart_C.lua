--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GameStart_C
local WBP_GameStart = UnLua.Class()

local IsFirstTimes = true;

-- 协程
local function run(self)
    UE.UKismetSystemLibrary.Delay(self, 0.5) -- 延迟一下
    self:Bind()
end

function WBP_GameStart:Construct()
    if(IsFirstTimes) then
        coroutine.resume(coroutine.create(run),self)
        IsFirstTimes = false;
    end
end

function WBP_GameStart:Bind()
    self.PlaceStageButton.OnClicked:Add(self, self.OnClickedPlace);
    self.StartStageButton.OnClicked:Add(self, self.OnClickedStart);
end

----------------------------- Event -----------------------------

function WBP_GameStart:OnClickedPlace()
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_PlaceButton();
    end
end

function WBP_GameStart:OnClickedStart()
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_GameStart();
    end
end




--function WBP_GameStart:Initialize(Initializer)
--end

--function WBP_GameStart:PreConstruct(IsDesignTime)
--end

--function WBP_GameStart:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GameStart
