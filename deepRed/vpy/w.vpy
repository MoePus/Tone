def getVideoSource():
    import vapoursynth as vs
    core = vs.get_core()
    clip = core.ffms2.Source(r'E:/racemiku2016/720PwithoutSubtitles.mp4')
    
    return clip
import vapoursynth as vs
core = vs.get_core()

clip = getVideoSource()
clip = core.std.Trim(clip,length=50)
clip.set_output().