--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GamePlay_C
local WBP_GamePlay = UnLua.Class()

local IsFirstTimes = true;

-- 协程
local function run(self)
    UE.UKismetSystemLibrary.Delay(self, 0.5) -- 延迟一下
    self:Bind()
end

function WBP_GamePlay:Construct()
    if(IsFirstTimes) then
        coroutine.resume(coroutine.create(run),self)
        IsFirstTimes = false;
    end
end

function WBP_GamePlay:Bind()
    self.ExitButton.OnClicked:Add(self, self.OnClickedExitButton);
    self.PauseButton.OnClicked:Add(self, self.OnClickedPauseButton);
end

------------------------- Event -------------------------

function WBP_GamePlay:OnClickedExitButton()
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_ExitButton();
    end
end

function WBP_GamePlay:OnClickedPauseButton()
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_PauseButton();
    end
end

--function WBP_GamePlay:Initialize(Initializer)
--end

--function WBP_GamePlay:PreConstruct(IsDesignTime)
--end

--function WBP_GamePlay:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GamePlay
