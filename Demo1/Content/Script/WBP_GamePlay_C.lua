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

function WBP_GamePlay:Construct()
    self:Bind()
    self:Init()
end

function WBP_GamePlay:Bind()
    self.PauseButton.OnClicked:Add(self, self.OnClickedPauseButton);
    self.ContinueButton.OnClicked:Add(self, self.OnClickedContinueButton);
    self.RestartButton.OnClicked:Add(self, self.OnClickedRestartButton);
    self.ExitButton.OnClicked:Add(self, self.OnClickedExitButton);
end

function WBP_GamePlay:Init()
    if(self.ButtonList:IsVisible()) then
        self.ButtonList:SetVisibility(UE.ESlateVisibility.Collapsed)
    end
end

------------------------- Event -------------------------

-- �˳���ť
function WBP_GamePlay:OnClickedExitButton()
    self:QuitGame();
end

-- ��ͣ��ť
function WBP_GamePlay:OnClickedPauseButton()
    self:PauseGame();   -- ��ͼ����ͣ��Ϸ
    self:IsShowButtonList(self.ButtonList,true);
    self:IsShowButtonList(self.PauseButton,false);
end

-- ������ť
function WBP_GamePlay:OnClickedContinueButton()
    self:ReleaseGame(); -- ��ͼ��������Ϸ
    self:IsShowButtonList(self.ButtonList,false);
    self:IsShowButtonList(self.PauseButton,true);
end

-- ���¿�ʼ��ť
function WBP_GamePlay:OnClickedRestartButton()
    -- self:ReleaseGame();
    self:RestartGame();
end


function WBP_GamePlay:IsShowButtonList(UI, flag)
    if(flag) then
        if(UI:IsVisible() == false) then
            UI:SetVisibility(UE.ESlateVisibility.Visible)
        end
    else
        if(UI:IsVisible()) then
            UI:SetVisibility(UE.ESlateVisibility.Collapsed)
        end
    end
end

--function WBP_GamePlay:Initialize(Initializer)
--end

--function WBP_GamePlay:PreConstruct(IsDesignTime)
--end

--function WBP_GamePlay:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GamePlay
