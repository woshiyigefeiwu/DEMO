--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GameOver_C
local WBP_GameOver = UnLua.Class()

function WBP_GameOver:Construct()
    self:PauseGame();   -- 蓝图，暂停游戏
    self:Bind()
end

function WBP_GameOver:Bind()
    self.RestartButton.OnClicked:Add(self, self.OnClickedRestartButton);
    self.ExitButton.OnClicked:Add(self, self.OnClickedExitButton);
end

------------------------- Event -------------------------

-- 退出按钮
function WBP_GameOver:OnClickedExitButton()
    self:QuitGame();
end

-- 重新开始按钮
function WBP_GameOver:OnClickedRestartButton()
    self:RestartGame();
end


--function WBP_GameOver:Initialize(Initializer)
--end

--function WBP_GameOver:PreConstruct(IsDesignTime)
--end

--function WBP_GameOver:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GameOver
