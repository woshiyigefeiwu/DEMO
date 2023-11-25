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

function WBP_GameStart:Construct()
    self:Bind() 
end

function WBP_GameStart:Bind()
    self.PlaceStageButton.OnClicked:Add(self, self.OnClickedPlace);
    self.StartStageButton.OnClicked:Add(self, self.OnClickedStart);

    -- self:PauseGame();   -- ¿∂Õº£¨‘›Õ£”Œœ∑
end

----------------------------- Event -----------------------------

function WBP_GameStart:OnClickedPlace()
    local GS = UE.UGameplayStatics.GetGameState(self);
    if(GS and GS:GetUIManager()) then
        local UIM = GS:GetUIManager();
        UIM:ShowUI("UI_SelectCamp");
    end
end

function WBP_GameStart:OnClickedStart()
    -- self:ReleaseGame();

    local GS = UE.UGameplayStatics.GetGameState(self);
    if(GS and GS:GetUIManager()) then
        local UIM = GS:GetUIManager();
        UIM:ShowUI("UI_GamePlay");
    end
end

--function WBP_GameStart:Initialize(Initializer)
--end

--function WBP_GameStart:PreConstruct(IsDesignTime)
--end

--function WBP_GameStart:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GameStart
